#include <animation/animation.hpp>

Animation::Animation(sf::Vector2i start, sf::Vector2i size, unsigned int frameCount){
    for(unsigned int f = 0; f < frameCount; ++f){
        frames.push_back(sf::IntRect(start, size));
        start.x += size.x;
    }
}

sf::IntRect Animation::nextFrame(){
    if(!repeats && currentFrame == frames.size() - 1){
        return frames[currentFrame];
    }
    currentFrame++;
    if(currentFrame >= frames.size()){

        currentFrame = 0;
    }

    return frames[currentFrame];
}

void Animation::reset(){
    currentFrame = 0;
}

sf::IntRect Animation::firstFrame(){
    return frames[0];
}

sf::IntRect Animation::transition(unsigned int frame){
    currentFrame = frame;
    return frames[currentFrame];
}

unsigned int Animation::getCurrentFrame(){
    return currentFrame;
}
