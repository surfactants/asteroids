#pragma once

#include <entity/player.hpp>
#include <entity/enemy.hpp>
#include <vector>
#include <world/world.hpp>
#include <entity/enemy_manager.hpp>
#include <entity/projectile_manager.hpp>
#include <system/collider.hpp>
#include <system/state_hook.hpp>
#include <audio/audio_manager.hpp>
#include <resources/texture_manager.hpp>

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