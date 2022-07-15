#include "animated_sprite.hpp"

Animated_Sprite::Animated_Sprite(sf::Texture& texture, sf::Vector2i nsize)
: size{ nsize }
{
    setTexture(texture);
    setAnimationState(IDLE);
    setDirection(randomDirection());
}

void Animated_Sprite::setAnimationState(Animation_State nstate){
    state = nstate;
    animationY = state * (size.y * 4);
    frame = 0;
    updateFrame();
}

void Animated_Sprite::setDirection(Direction ndirection){
    direction = ndirection;
    directionY = direction * size.y;
    updateFrame();
}

Direction Animated_Sprite::getDirection(){
    return direction;
}

void Animated_Sprite::update(){
    if(state == DYING && frame == frameLimit) return;
    else if(frameTimer.getElapsedTime().asMilliseconds() >= frameThreshold){
        frameTimer.restart();
        if(frame == frameLimit) frame = 0;
        else frame++;
        updateFrame();
    }
}

void Animated_Sprite::updateFrame(){
    setTextureRect(sf::IntRect(sf::Vector2i(frame * size.x, animationY + directionY), size));
}
