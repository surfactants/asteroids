#include "player.hpp"
#include "texture_manager.hpp"
#include <iostream>

Player::Player(){
    hMove = NULLSIDE;
    vMove = NULLSIDE;

    texture.loadFromFile("textures/entity.png");

    std::cout << "\nhere";
    sprite = Animated_Sprite(*Texture_Manager::get("player"), sf::Vector2i(64, 64));

    std::cout << "\nhere";
}

void Player::update(){
    sprite.update();
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

    bool v = (vMove != NULLSIDE);
    bool h = (hMove != NULLSIDE);

    bool wasd = (w || a || s || d);

    if((v || h)){
        if(!wasd){
            stop();
            vMove = NULLSIDE;
            hMove = NULLSIDE;
            return;
        }
        else{
            if(v && !w && !s){
                vMove = NULLSIDE;
                stopVertical();
                setSpriteDirection();
            }
            if(h && !a && !d){
                hMove = NULLSIDE;
                stopHorizontal();
                setSpriteDirection();
            }
        }
    }

    if(v && !(w || s)){
       vMove = NULLSIDE;
       setSpriteDirection();
    }
    else if(vMove != NORTH && w){
        vMove = NORTH;
        directUp();
    }
    else if(vMove != SOUTH && s){
        vMove = SOUTH;
        directDown();
    }

    if(h && !(a || d)){
        hMove = NULLSIDE;
        setSpriteDirection();
    }
    else if(hMove != EAST && d){
        hMove = EAST;
        directRight();
    }
    else if(hMove != WEST && a){
        hMove = WEST;
        directLeft();
    }

    //IF NOT MOVING:
        //NO KEYS PRESSED:
            //RETURN
        //ANY KEY PRESSED:
            //SET ANIMATION STATE TO MOVING
            //SET HMOVE AND VMOVE BASED ON KEYS PRESSED

    //ELSE IF MOVING:
        //NO KEYS PRESSED:
            //SET ANIMATION STATE TO IDLE
        //KEYS PRESSED
            //IF(!DIRECTION && D_KEY_PRESSED):
                //DIRECT IN THAT DIRECTION
}

void Player::upStart(){
    if(!up){
        up = true;
    }
}

void Player::upEnd(){
    if(up){
        up = false;
    }
}

void Player::downStart(){
    if(!down){
        down = true;
        setVelocity();
    }
}

void Player::downEnd(){
    if(down){
        down = false;
        setVelocity();
    }
}

void Player::leftStart(){
    if(!left){
        left = true;
        setVelocity();
    }
}

void Player::leftEnd(){
    if(left){
        left = false;
        setVelocity();
    }
}

void Player::rightStart(){
    if(!right){
        right = true;
        setVelocity();
    }
}

void Player::rightEnd(){
    if(right){
        right = false;
        setVelocity();
    }
}
