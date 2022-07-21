#include "menu.hpp"
#include <iostream>

std::vector<Nav> Menu::nav = std::vector<Nav>();
Nav::Nav(std::string nlabel, sf::Font& font, Main_State ntmain, Menu_State ntmenu)
: Button{ nlabel, font }{
    target_main = ntmain;
    target_menu = ntmenu;
}

sf::Font Menu::font = sf::Font();

Menu::Menu(){
    if(!font.loadFromFile("adventpro-bold.ttf")){
        std::cout << "\nfont failed to load!";
    }

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
        std::cout << "\n\t\t" << "checking nav...";
        if(button.isHighlighted()){
            std::cout << "\n\t\tbutton clicked!";
            if(button.target_main != MAIN_NULL){
                newMain(button.target_main);
            }
            if(button.target_menu != MENU_NULL){
                newMenu(button.target_menu);
            }
            return;
        }
        std::cout << "\n\tno nav highlight found...";
    }
    for(auto& button : options){
        std::cout << "\n\t\t" << "checking options...";
        if(button.second.isHighlighted()){
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
    std::cout << "\nmenu unclick detected...";
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
    for(auto& button : options) button.second.update(mpos);
    for(auto& slider : sliders) slider.second.update();
}

void Menu::back(){
    if(escape != MAIN_NULL){
        newMain(escape);
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& button : nav) target.draw(button, states);
    for(const auto& button : options) target.draw(button.second, states);
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
}

void Menu_Settings::back(){
    newMenu(prev_menu);
}
