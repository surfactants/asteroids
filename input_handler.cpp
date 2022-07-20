#include "input_handler.hpp"
#include "key_to_char.hpp"

Input_Handler::Input_Handler(sf::RenderWindow& nwindow, Game& game, UI& ui, Menu* menu)
: window{ nwindow }{
    Player* player = &game.getPlayer();
    Input_Package& p_g = context[MAIN_GAME];

    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('w', std::bind(&Player::upStart, player)));
    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('w', std::bind(&Player::upEnd, player)));

    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('s', std::bind(&Player::downStart, player)));
    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('s', std::bind(&Player::downEnd, player)));

    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('a', std::bind(&Player::leftStart, player)));
    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('a', std::bind(&Player::leftEnd, player)));

    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('d', std::bind(&Player::rightStart, player)));
    p_g.keyPressed.insert(std::make_pair<char, std::function<void()>>('d', std::bind(&Player::rightEnd, player)));

    Input_Package& p_m = context[MAIN_MENU];

    p_m.left_click = std::bind(&Menu::clickLeft, menu);
    p_m.left_release = std::bind(&Menu::releaseLeft, menu);
    p_m.right_click = std::bind(&Menu::clickRight, menu);
    p_m.right_release = std::bind(&Menu::releaseRight, menu);
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
                char c = keyToChar(event);
                if(context[state_main].keyPressed.count(c)){
                    context[state_main].keyPressed[c]();
                }
            }
            else if(event.type == sf::Event::KeyReleased){
                char c = keyToChar(event);
                if(context[state_main].keyReleased.count(c)){
                    context[state_main].keyReleased[c]();
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed){
                if(event.mouseButton.button == sf::Mouse::Left){
                    context[state_main].left_click();
                }
                else if(event.mouseButton.button == sf::Mouse::Right){
                    context[state_main].right_click();
                }
            }
            else if(event.type == sf::Event::MouseButtonReleased){
                if(event.mouseButton.button == sf::Mouse::Left){
                    context[state_main].left_release();
                }
                else if(event.mouseButton.button == sf::Mouse::Right){
                    context[state_main].right_release();
                }
            }
        }
    }
}
