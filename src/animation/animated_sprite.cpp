#include <animation/animated_sprite.hpp>

Animated_Sprite::Animated_Sprite(sf::Texture& texture, sf::Vector2i nsize, std::map<Entity_State, unsigned int> counts)
: size{ nsize }
{
    loadCounts(counts);
    setTexture(texture);
    direction = randomDirection();
    setAnimationState(IDLE);
    setOrigin(sf::Vector2f(size) / 2.f);
}

void Animated_Sprite::setAnimationState(Entity_State nstate){
    animations[state][direction].reset();
    state = nstate;
    setTextureRect(animations[state][direction].firstFrame());
    //load frameThreshold here
}

void Animated_Sprite::setDirection(Direction ndirection){
    if(direction != ndirection){
        Direction mirror = ndirection;
        if(direction > SOUTH && ndirection < SOUTH){
            setScale(1.f, 1.f);
        }
        else if(ndirection > SOUTH){
            mirror = mirrorDirection(ndirection);
            if(direction <= SOUTH){
                setScale(-1.f, 1.f);
            }
        }
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

Entity_State Animated_Sprite::getState(){
    return state;
}
