#pragma once

#include <abilities/projectile_manager.hpp>
#include <ai/ai.hpp>
#include <entity/enemy.hpp>
#include <entity/enemy_manager.hpp>
#include <entity/faction.hpp>
#include <entity/player.hpp>
#include <resources/texture_manager.hpp>
#include <system/collider.hpp>
#include <system/state_hook.hpp>
#include <vector>
#include <world/world.hpp>

#include "game_state.hpp"

class Game : public sf::Drawable, public State_Hook {
public:
    Game(sf::RenderWindow& nwindow, sf::View& nview);
    void update(float deltaTime);
    void enter();
    Player& getPlayer();
    World& getWorld();
    void newLevel();
    void spawnEnemies();

    std::vector<sf::Vector2f> getRelativeEnemyPositions();

    std::vector<Enemy>& getEnemies();

    void clickLeft();
    void releaseLeft();

    void escape();

    void stopInput();

    void scroll(float delta);

    Game_State getState();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    //Texture_Manager textures;

    Faction enemyFaction;

    World world { enemyFaction };
    //Level level;

    size_t closestEnemyIndex { SIZE_MAX };

    Player player;

    Enemy_Manager enemyManager { enemyFaction };

    Projectile_Manager projectileManager;

    sf::RenderWindow& window;
    sf::View& view;

    sf::Clock tickClock;

    void playerShoot();

    Collider collider;

    bool levelEnding = false;

    sf::Clock endTimer;
    const static float endThreshold;

    void checkWin();

    std::map<std::string, Ability> abilities;

    AI ai;

    Game_State state { Game_State::PEACE };
};
