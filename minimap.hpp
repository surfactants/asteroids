#pragma once

#include <SFML/Graphics.hpp>
#include "enemy.hpp"

class Minimap : public sf::Drawable{
public:
    Minimap();
    void update(std::vector<sf::Vector2f> epos);
    void readBlip(sf::Vector2f pos);
    void set(sf::Vector2f size);
protected:
private:
    sf::View view;

    sf::RectangleShape backdrop;

    sf::CircleShape frame;
    sf::CircleShape center;

    struct Blip : public sf::CircleShape{
        Blip();
        Blip(sf::Vector2f pos);
        sf::Clock decayClock;
        void update();
        void reset();
        uint8_t r = 250, g = 75, b = 75;
        void refill();

        bool dead = false;
    };
    std::vector<Blip> blips;
    sf::RectangleShape line;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
