#pragma once

#include "player.hpp"
#include "enemy.hpp"
#include "room.hpp"
#include <vector>

class Enemy_Manager : public sf::Drawable{
public:
    Enemy_Manager();

    void spawn(std::vector<Room>& rooms, float tileSize);
    void clear();

    std::vector<Enemy>& getEnemies();

    Faction currentFaction;

private:
    std::vector<Enemy> enemies;

    std::map<Faction, std::map<Entity_Type, Enemy>> prototypes;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    unsigned int lowLevel, highLevel;

    void loadPrototypes();
};
