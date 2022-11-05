#pragma once

#include <entity/enemy.hpp>
#include <vector>
#include <world/room.hpp>

class Enemy_Manager : public sf::Drawable {
public:
    Enemy_Manager(Faction& f);

    void spawn(std::vector<Room>& rooms, float tileSize);
    void clear();

    std::vector<Enemy>& getEnemies();

    Faction& enemyFaction;

    bool checkFinalBoss();

private:
    std::vector<Enemy> enemies;

    std::map<Faction, std::map<Entity_Type, Enemy>> prototypes;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    unsigned int lowLevel, highLevel;

    void loadPrototypes();

    void reset();
};
