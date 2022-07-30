#include <animation/animated_sprite.hpp>
#include <iostream>
#include <util/vector2_stream.hpp>

Animated_Sprite::Animated_Sprite(sf::Texture& texture, sf::Vector2i nsize, std::map<Entity_State, unsigned int> counts)
: size{ nsize }
{
    std::cout << "\nnew entity";
    loadCounts(counts);
    setTexture(texture);
    direction = NORTH;
    direction = randomDirection();
    setAnimationState(IDLE);
    setOrigin(sf::Vector2f(size) / 2.f);
}

void Animated_Sprite::setAnimationState(Entity_State nstate){
    if(state != nstate){
        animations[state][direction].reset();
        state = nstate;
        std::cout << "\n\tsetting animation state to _" << entityStateToString(state) << "_" << directionToString(direction) << "_";
        setTextureRect(animations[state][direction].firstFrame());
        //load frameThreshold here
    }
}

void Animated_Sprite::setDirection(Direction ndirection){
    if(direction != ndirection){
        Direction mirror = ndirection;
        setTextureRect(animations[state][ndirection].transition(animations[state][mirror].getCurrentFrame()));
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
    if(state == DYING && animations[state][direction].lastFrame()){
        state = DEAD;
    }
}

void Animated_Sprite::updateFrame(){
    setTextureRect(animations[state][direction].nextFrame());
}

Entity_State Animated_Sprite::getAnimationState(){
    return state;
}

void Animated_Sprite::loadCounts(std::map<Entity_State, unsigned int> times){
    const int dlimit = static_cast<int>(NULLSIDE);
    std::cout << "\n\t\t";
    for(auto& t : times){
        for(unsigned int i = 0; i < dlimit; ++i){
            sf::Vector2i start(0, static_cast<int>(t.first) * (size.y * 5));
            Direction d = static_cast<Direction>(i);

            start.y += (i * size.y);

            sf::Vector2i aSize = size;

            if(d > SOUTH) aSize.x *= -1;


    std::cout << "\nconstructing animation " << entityStateToString(t.first) << "-" << directionToString(static_cast<Direction>(i)) << ": " << start << " | size " << aSize << " | framecount " << t.second;
            animations[t.first][d] = Animation(start, aSize, t.second);
            if(t.first == DYING) animations[t.first][d].repeats = false;
        }
    }
}

Entity_State Animated_Sprite::getState(){
    return state;
}
