#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <SFML/System/Clock.hpp>

#include "sound.hpp"

struct Sound_Context {
    Sound_Context() = default;
    Sound_Context(sf::SoundBuffer buffer, float threshold) :
        buffer{ buffer }, threshold{ threshold }{}

    sf::SoundBuffer buffer;
    sf::Clock clock;
    float threshold;

    bool ready()
    {
        if (clock.getElapsedTime().asSeconds() >= threshold) {
            clock.restart();
            return true;
        }
        return false;
    }
};
