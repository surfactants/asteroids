#include <menu/menu.hpp>
#include <system/database.hpp>
#include <resources/font_manager.hpp>

std::vector<Nav> Menu::nav = std::vector<Nav>();

sf::Font& Menu::font = Font_Manager::get(FONT_MENU);

Menu::Menu(){
    sf::Vector2f pos(256.f, 128.f);

    nav.push_back(Nav("new game", font, MAIN_NEWGAME, MENU_PAUSE));
        nav.back().setPosition(pos);
        pos.y += 128.f;

    nav.push_back(Nav("settings", font, MAIN_MENU, MENU_SETTINGS));
        nav.back().setPosition(pos);
        pos.y += 128.f;

    nav.push_back(Nav("quit", font, MAIN_QUIT, MENU_NULL));
        nav.back().setPosition(pos);
}

void Menu::clickLeft(){
    for(auto& button : nav){
        if(button.isHighlighted()){
            if(button.target_main != MAIN_NULL){
                newMain(button.target_main);
            }
            if(button.target_menu != MENU_NULL){
                newMenu(button.target_menu);
            }
            return;
        }
    }
    for(auto& option : options){
        if(option.isHighlighted()){
            option.target();
            return;
        }
    }
    for(auto& slider : sliders){
        if(slider.second.click()){
            break;
        }
    }
}

void Menu::clickRight(){
}

void Menu::releaseLeft(){
    for(auto& slider : sliders){
        if(slider.second.unclick()){
            return;
        }
    }
}

void Menu::scroll(float delta){
    for(auto& slider : sliders){
        if(slider.second.checkMouse()){
            slider.second.scroll(delta);
            break;
        }
    }
}

void Menu::releaseRight(){}

void Menu::update(sf::Vector2f mpos){
    for(auto& button : nav) button.update(mpos);
    for(auto& option : options) option.update(mpos);
    for(auto& slider : sliders) slider.second.update();
}

void Menu::back(){
    if(escape != MAIN_NULL){
        newMain(escape);
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& button : nav) target.draw(button, states);
    for(const auto& option : options) target.draw(option, states);
    for(const auto& slider : sliders) target.draw(slider.second, states);
}

Menu_Main::Menu_Main(){
    escape = MAIN_QUIT;
}

Menu_Pause::Menu_Pause(){
    escape = MAIN_GAME;
}

Menu_Settings::Menu_Settings(){
    sliders[VOL_MUSIC] = Slider("music volume");

    sliders[VOL_GAME] = Slider("game volume");

    sliders[VOL_UI] = Slider("ui volume");

    sf::Vector2f spos(544.f, 0.f);

    for(auto& slider : sliders){
        spos.y += 128.f;
        slider.second.set(spos, font);
    }

    spos.y += 256.f;

    options.push_back(Option("save", font, std::bind(&Menu::saveSettings, this)));
    options.back().setPosition(spos);

    spos.x += 256.f;

    options.push_back(Option("cancel", font, std::bind(&Menu::back, this)));
    options.back().setPosition(spos);

    loadSettings();
}

void Menu_Settings::back(){
    reset();
    newMenu(prev_menu);
}

void Menu_Settings::saveSettings(){
    setVolumeMusic(sliders[VOL_MUSIC].getFill());
    setVolumeGame(sliders[VOL_GAME].getFill());
    setVolumeUI(sliders[VOL_UI].getFill());
    Database::saveSettings(generateSettingsPackage());
    back();
}

Settings_Package Menu_Settings::generateSettingsPackage(){
    Settings_Package p;

        p.volume[VOL_MUSIC] = getVolumeMusic();
        p.volume[VOL_GAME] = getVolumeGame();
        p.volume[VOL_UI] = getVolumeUI();

    return p;
}

void Menu_Settings::reset(){
    sliders[VOL_MUSIC].setFill(getVolumeMusic());
    sliders[VOL_GAME].setFill(getVolumeGame());
    sliders[VOL_UI].setFill(getVolumeUI());
}

void Menu_Settings::loadSettings(){
    Settings_Package p = Database::getSettings();
        setVolumeMusic(p.volume[VOL_MUSIC]);
        setVolumeGame(p.volume[VOL_GAME]);
        setVolumeUI(p.volume[VOL_UI]);
    reset();
}

void Menu::stopInput(){
    releaseLeft();
}
