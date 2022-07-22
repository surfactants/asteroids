#include "animation.hpp"

sf::IntRect Animation::nextFrame(){
    frame++;
    if(frame >= frames.size()){
        frame = 0;
    }

    return frames[frame];
}
