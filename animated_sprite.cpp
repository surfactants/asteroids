#include "animated_sprite.hpp"

Animated_Sprite::Animated_Sprite(sf::Texture& texture, sf::Vector2i nsize, std::map<Animation_State, unsigned int> counts)
: size{ nsize }
{
    loadCounts(counts);
    setTexture(texture);
    direction = randomDirection();
    setAnimationState(IDLE);
    setOrigin(sf::Vector2f(size) / 2.f);
}

void Animated_Sprite::setAnimationState(Animation_State nstate){
    animations[state][direction].reset();
    state = nstate;
    setTextureRect(animations[state][direction].firstFrame());
    //load frameThreshold here
}

void Animated_Sprite::setDirection(Direction ndirection){
    if(direction != ndirection){
        setTextureRect(animations[state][ndirection].transition(animations[state][direction].getCurrentFrame()));
        animations[state][direction].reset();
        direction = ndirection;
    }
}

Direction Animated_Sprite::getDirection(){
    return direction;
}

void Animated_Sprite::update(){
    if(frameTimer.getElapsedTime().asMilliseconds() >= frameThreshold){
        frameTimer.restart();
        updateFrame();
    }
}

void Animated_Sprite::updateFrame(){
    setTextureRect(animations[state][direction].nextFrame());
}

Animation_State Animated_Sprite::getAnimationState(){
    return state;
}

void Animated_Sprite::loadCounts(std::map<Animation_State, unsigned int> times){
    for(auto& t : times){
        for(unsigned int i = 0; i < 4; ++i){
            sf::Vector2i start(0, static_cast<int>(t.first) * (size.y * 4));
            start.y += (i * size.y);
            Direction d = static_cast<Direction>(i);

            animations[t.first][d] = Animation(start, size, t.second);
            if(t.first == DYING) animations[t.first][d].repeats = false;
        }
    }
}
