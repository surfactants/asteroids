#pragma once

#include "floor.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include <vector>
#include "world.hpp"
#include "enemy_manager.hpp"
#include "projectile_manager.hpp"
#include "collider.hpp"
#include "state_hook.hpp"
#include "audio_manager.hpp"
#include "texture_manager.hpp"

class Game : public sf::Drawable, public State_Hook{
public:
    Game(sf::RenderWindow& nwindow, sf::View& nview);
    void update();
    void enter();
    Player& getPlayer();
    World& getWorld();
    void newLevel();
    void spawnEnemies();

    std::vector<sf::Vector2f> getEnemyPositions();

    std::vector<Enemy>& getEnemies();

    void clickLeft();
    void releaseLeft();

    void escape();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Texture_Manager textures;

    World world;
    //Level level;

    Player player;
        std::vector<sf::FloatRect> getPlayerCollideMap();

    Enemy_Manager enemyManager;

    Projectile_Manager projectileManager;

    sf::RenderWindow& window;
    sf::View& view;

    sf::Clock tickClock;

    void playerShoot();

    Collider collider;

    Audio_Game audio;
};
