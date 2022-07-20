#include "input_handler.hpp"
#include "key_to_char.hpp"
#include <iostream>

void Input_Package::clear(){
    keyPressed.clear();
    keyReleased.clear();
    mouse.clear();
}

Input_Handler::Input_Handler(sf::RenderWindow& nwindow, Game& game, UI& ui, Menu_Package m)
: window{ nwindow }{
    Player* player = &game.getPlayer();

    /////////////////////////////////////////////////////////////
    Input_Package& p_g = context[MAIN_GAME];

    p_g.keyPressed['w'] = std::bind(&Player::upStart, player);
    p_g.keyReleased['w'] = std::bind(&Player::upEnd, player);

    p_g.keyPressed['s'] = std::bind(&Player::downStart, player);
    p_g.keyReleased['s'] = std::bind(&Player::downEnd, player);

    p_g.keyPressed['a'] = std::bind(&Player::leftStart, player);
    p_g.keyReleased['a'] = std::bind(&Player::leftEnd, player);

    p_g.keyPressed['d'] = std::bind(&Player::rightStart, player);
    p_g.keyReleased['d'] = std::bind(&Player::rightEnd, player);

    p_g.mouse[LEFT_CLICK] = std::bind(&UI::clickLeft, &ui);
    p_g.mouse[LEFT_RELEASE] = std::bind(&UI::releaseLeft, &ui);

    /////////////////////////////////////////////////////////////
    Input_Package& p_m = context_menu[MENU_MAIN];

    p_m.mouse[LEFT_CLICK] = std::bind(&Menu::clickLeft, m.m_main);
    p_m.mouse[LEFT_RELEASE] = std::bind(&Menu::releaseLeft, m.m_main);

    Input_Package& p_p = context_menu[MENU_PAUSE];
    p_p.mouse[LEFT_CLICK] = std::bind(&Menu::clickLeft, m.m_pause);
    p_p.mouse[LEFT_RELEASE] = std::bind(&Menu::releaseLeft, m.m_pause);

    Input_Package& p_s = context_menu[MENU_SETTINGS];
    p_s.mouse[LEFT_CLICK] = std::bind(&Menu::clickLeft, m.m_settings);
    p_s.mouse[LEFT_RELEASE] = std::bind(&Menu::releaseLeft, m.m_settings);
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
                char c = keyToChar(event.key.code);
                if(context[state_main].keyPressed.count(c)){
                    context[state_main].keyPressed[c]();
                }
            }
            else if(event.type == sf::Event::KeyReleased){
                char c = keyToChar(event.key.code);
                    std::cout << "\nkey release detected, char " << c;
                if(context[state_main].keyReleased.count(c)){
                    context[state_main].keyReleased[c]();
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
        }
    }
}

void Input_Handler::menuChange(){
    context[MAIN_MENU].clear();
    context[MAIN_MENU] = context_menu[state_menu];
}


