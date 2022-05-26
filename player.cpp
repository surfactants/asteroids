#include "player.hpp"

Player::Player(){
    hMove = NULLSIDE;
    vMove = NULLSIDE;
}

void Player::update(){
    checkWASD();
    //Entity::update();
}

void Player::checkWASD(){
    bool w = (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

    bool a = (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));

    bool s = (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    bool d = (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    if(vMove == NULLSIDE && w){
        vMove = UP;
        directUp();
    }
    else if(vMove == NULLSIDE && s){
        vMove = DOWN;
        directDown();
    }
    else if(vMove == UP && !w){
        vMove = NULLSIDE;
        stopVertical();
    }
    else if(vMove == DOWN && !s){
        vMove = NULLSIDE;
        stopVertical();
    }

    if(hMove == NULLSIDE && a){
        hMove = LEFT;
        directLeft();
    }
    else if(hMove == NULLSIDE && d){
        hMove = RIGHT;
        directRight();
    }
    else if(hMove == LEFT && !a){
        hMove = NULLSIDE;
        stopHorizontal();
    }
    else if(hMove == RIGHT && !d){
        hMove = NULLSIDE;
        stopHorizontal();
    }
}
