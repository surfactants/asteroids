#pragma once

#include "player.hpp"
#include "enemy.hpp"
#include "room.hpp"

class Enemy_Manager : public sf::Drawable{
public:
    Enemy_Manager();

    void spawn(std::vector<Room>& rooms, float tileSize);
    void clear();

private:
    std::vector<Enemy> enemies;

    Enemy boss;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    unsigned int lowLevel, highLevel;
};
