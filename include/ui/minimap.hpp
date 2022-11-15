#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/System/Clock.hpp>

#include <entity/enemy.hpp>

class Minimap : public sf::Drawable {
public:
    Minimap();
    void initialize(std::vector<Enemy>& enemies, sf::Vector2f playerPos);
    void update(std::vector<Enemy>& enemies, sf::Vector2f playerPos);
    void readBlip(sf::Vector2f pos);
    void set(sf::Vector2f size);

protected:
private:
    sf::View view;

    sf::RectangleShape backdrop;

    sf::CircleShape frame;
    sf::CircleShape center;

    sf::Clock rotateClock;
    const static float rotateThreshold;

    struct Blip : public sf::CircleShape {
        Blip();
        Blip(sf::Vector2f pos);
        sf::Clock decayClock;
        void update();
        void reset();
        const static uint8_t r = 250, g = 75, b = 75;
        uint8_t a = 255;
        void refill();
        bool ready();

        sf::Clock timer;
        const static float timeThreshold;

        bool dead = false;
    };
    std::map<unsigned int, Blip> blips;
    std::vector<Blip> dyingBlips;
    sf::RectangleShape line;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
