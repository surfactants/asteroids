#include "player.hpp"
#include "texture_manager.hpp"
#include <iostream>

Player::Player(){
    hMove = NULLSIDE;
    vMove = NULLSIDE;

    sprite = Animated_Sprite(*Texture_Manager::get("PLAYER"), sf::Vector2i(64, 64));
}

void Player::update(){
    sprite.update();
}

void Player::upStart(){
    if(!up){
        up = true;
        setVelocity();
    }
}

void Player::upEnd(){
    if(up){
        up = false;
        setVelocity();
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
        std::cout << "\nplayer left end";
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
