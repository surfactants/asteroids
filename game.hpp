#pragma once

#include "floor.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <vector>
#include "world.hpp"
#include "enemy_manager.hpp"

class Game : public sf::Drawable{
public:
    Game(sf::RenderWindow& nwindow);
    void update(sf::View& viewGame);
    void enter();
    Player& getPlayer();
    World& getWorld();
    void newLevel();
    void spawnEnemies();

    bool readEvent(sf::Event& event, sf::Vector2f mPos);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    World world;
    //Level level;

    Player player;
        std::vector<sf::FloatRect> getPlayerCollideMap();

    Enemy_Manager enemyManager;

    sf::Clock tickClock;

    sf::View worldView;

    sf::RenderWindow& window;
};
