#include <animation/animation.hpp>
#include <iostream>
#include <util/vector2_stream.hpp>

Animation::Animation(sf::Vector2i start, sf::Vector2i size, unsigned int frameCount){
    for(unsigned int f = 0; f < frameCount; ++f){
        std::cout << "\n\t\t" << start.x;
        frames.push_back(sf::IntRect(start, size));
        start.x += std::abs(size.x);
    }
    std::cout << "\n\tconstructed! " << frames.size() << " frames";
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
    std::cout << "\nmade it to firstFrame";
    reset();
    std::cout << "\nsuccessful reset, returning frame 0 out of size " << frames.size();
    return frames[0];
}

sf::IntRect Animation::transition(unsigned int frame){
    currentFrame = frame;
    return frames[currentFrame];
}

unsigned int Animation::getCurrentFrame(){
    return currentFrame;
}

bool Animation::lastFrame(){
    return (currentFrame == frames.size() - 1);
}
