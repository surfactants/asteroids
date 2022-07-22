#pragma once

#include <SFML/Graphics.hpp>

enum Animation_State{
    MOVING,
    DYING,
    IDLE
};

class Animation{
public:
    Animation(std::vector<sf::IntRect> nframes) : frames{ nframes }{}
    sf::IntRect nextFrame();

private:
    unsigned int currentFrame = 0;
    std::vector<sf::IntRect> frames;
};
