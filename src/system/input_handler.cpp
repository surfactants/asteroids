#include <system/input_handler.hpp>

Input_Package::Input_Package(){
    clear();
}

void Input_Package::clear(){
    keyPressed.clear();
    keyReleased.clear();
    mouse.clear();

    scroll = std::function<void( float )>( [](float a){ return; } );
}

Input_Handler::Input_Handler(sf::RenderWindow& nwindow, Game& game, UI& ui, Menu_Package menu_package)
: window{ nwindow }{
    Player* player = &game.getPlayer();

    /////////////////////////////////////////////////////////////
    //GAME AND UI INPUTS
    //
    Input_Package& p_g = context[MAIN_GAME];

        p_g.keyReleased[sf::Keyboard::Escape] = std::bind(&Game::escape, &game);

        p_g.keyPressed[sf::Keyboard::W] = std::bind(&Player::upStart, player);
        p_g.keyReleased[sf::Keyboard::W] = std::bind(&Player::upEnd, player);

        p_g.keyPressed[sf::Keyboard::S] = std::bind(&Player::downStart, player);
        p_g.keyReleased[sf::Keyboard::S] = std::bind(&Player::downEnd, player);

        p_g.keyPressed[sf::Keyboard::A] = std::bind(&Player::leftStart, player);
        p_g.keyReleased[sf::Keyboard::A] = std::bind(&Player::leftEnd, player);

        p_g.keyPressed[sf::Keyboard::D] = std::bind(&Player::rightStart, player);
        p_g.keyReleased[sf::Keyboard::D] = std::bind(&Player::rightEnd, player);

        p_g.mouse[LEFT_CLICK] = std::bind(&UI::clickLeft, &ui);
        p_g.mouse[LEFT_RELEASE] = std::bind(&UI::releaseLeft, &ui);

        p_g.focus_lost = std::bind(&Game::stopInput, &game);

    /////////////////////////////////////////////////////////////
    //MENU INPUTS
    //
    std::vector<Menu*> m = { menu_package.m_main, menu_package.m_pause, menu_package.m_settings };
    std::vector<Menu_State> state = { MENU_MAIN, MENU_PAUSE, MENU_SETTINGS };

    for(unsigned int i = 0; i <= m.size(); ++i){
        Input_Package& p = context_menu[state[i]];
        p.keyReleased[sf::Keyboard::Escape] = std::bind(&Menu::back, m[i]);
        p.mouse[LEFT_CLICK] = std::bind(&Menu::clickLeft, m[i]);
        p.mouse[LEFT_RELEASE] = std::bind(&Menu::releaseLeft, m[i]);
        p.scroll = std::bind(&Menu::scroll, m[i], std::placeholders::_1);
        p.focus_lost = std::bind(&Menu::stopInput, m[i]);
    }
}

void Input_Handler::handle(){
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        else{
            if(state_main == MAIN_LOADING
            || state_main == MAIN_NEWGAME
            || state_main == MAIN_NULL
            || state_main == MAIN_QUIT){
                continue;
            }

            if(event.type == sf::Event::KeyPressed){
                if(context[state_main].keyPressed.count(event.key.code)){
                    context[state_main].keyPressed[event.key.code]();
                }
            }
            else if(event.type == sf::Event::KeyReleased){
                if(context[state_main].keyReleased.count(event.key.code)){
                    context[state_main].keyReleased[event.key.code]();
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left && context[state_main].mouse.count(LEFT_CLICK)){
                        context[state_main].mouse[LEFT_CLICK]();
                }
                else if(event.mouseButton.button == sf::Mouse::Right && context[state_main].mouse.count(RIGHT_CLICK)){
                    context[state_main].mouse[RIGHT_CLICK]();
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    if(context[state_main].mouse.count(LEFT_RELEASE)){
                       context[state_main].mouse[LEFT_RELEASE]();
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right){
                    if(context[state_main].mouse.count(RIGHT_RELEASE)){
                       context[state_main].mouse[RIGHT_RELEASE]();
                    }
                }
            }
            else if(event.type == sf::Event::MouseWheelScrolled){
                context[state_main].scroll(event.mouseWheelScroll.delta);
            }
            else if(event.type == sf::Event::LostFocus){
                context[state_main].focus_lost();
            }
        }
    }
}

void Input_Handler::menuChange(){
    context[MAIN_MENU].clear();
    context[MAIN_MENU] = context_menu[state_menu];
}


