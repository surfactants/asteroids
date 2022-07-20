#include "input_manager.hpp"

Input_Manager::Input_Manager(sf::RenderWindow& nwindow, Game& ngame, UI& nui, Menu* nmenu)
: window{ nwindow }, game{ ngame }, ui{ nui }, menu{ nmenu }{}

void Input_Manager::update(){

    //get from context[state_main] instead of another one of these control flow monstrosities

    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        else{
            switch(state_main){
            case MAIN_MENU:
                if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        menu->click();
                    }
                }
                else if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        menu->unclick();
                    }
                }
                break;
            case MAIN_GAME:
                if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right){
                    }
                }
                else if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left){
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right){
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}
