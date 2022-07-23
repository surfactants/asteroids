#pragma once

#include <SFML/Graphics.hpp>

enum Animation_State{
    MOVING,
    DYING,
    IDLE
};

class Animation{
public:
    Animation(){}
    Animation(sf::Vector2i start, sf::Vector2i size, unsigned int frameCount);
    sf::IntRect nextFrame();

    bool repeats = true;

    void reset();

    sf::IntRect firstFrame();

    sf::IntRect transition(unsigned int frame);

    unsigned int getCurrentFrame();

private:
    unsigned int currentFrame = 0;
    std::vector<sf::IntRect> frames;
};
