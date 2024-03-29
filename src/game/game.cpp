#include <game/game.hpp>

#include <system/database.hpp>

#include <util/fmouse.hpp>
#include <util/primordial.hpp>
#include <util/prng.hpp>

//////////////////////////////////////////////////////////////

const float Game::endThreshold = 3.f;

const float Game::interactThreshold = 64.f;

Game::Game(sf::RenderWindow& nwindow, sf::View& nview)
    : window { nwindow }
    , view { nview }
{
    player = Player(Database::getPlayerData(), Texture_Manager::get("PLAYER"));

    abilities = Database::getAbilities();

    player.addAbility(abilities["SHOOT"]);
    player.addAbility(abilities["KNIFE"]);
    player.addAbility(abilities["ROLL"]);
    player.addAbility(abilities["SNIPE"]);

    player.setPlayerAbilities();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(world, states);
    target.draw(enemyManager, states);
    target.draw(player, states);
    target.draw(projectileManager, states);
}

void Game::update(float deltaTime)
{
    if (tickClock.getElapsedTime().asSeconds() >= 1.f) {
        tickClock.restart();
    }

    collider.checkProjectiles(projectileManager.getProjectiles(),
        enemyManager.getEnemies(),
        player,
        world);
    for (auto& enemy : enemyManager.getEnemies()) {
        ai.decide(enemy, player);
        enemy.update();
        enemy.move(world.getLocalWalls(enemy.getCoordinates(Tile::tileSize)), deltaTime);
    }
    player.update();
    view.move(player.move(world.getLocalWalls(player.getCoordinates(Tile::tileSize)), deltaTime));

    player.setTarget(fMouse(window, view));

    if (player.readyToCast()) {
        projectileManager.create(player.cast());
    }

    projectileManager.update(deltaTime);

    checkWin();
}

void Game::checkWin()
{
    if (levelEnding) {
        if (endTimer.getElapsedTime().asSeconds() >= endThreshold) {
            newMain(Main_State::NEWGAME);
            stopInput();
            levelEnding = false;
        }
    }
    else if (enemyManager.checkFinalBoss()) {
        levelEnding = true;
        endTimer.restart();
    }
}

Player& Game::getPlayer()
{
    return player;
}

void Game::enter()
{
}

void Game::newLevel()
{
    player.setPosition(sf::Vector2f(0.f, 0.f));
    view.setCenter(player.getPosition());
    world.reset();
    enemyFaction = randomEnemyFaction();
    if (prng::boolean()) {
        enemyFaction = Faction::BUGS; /* DEBUG / TESTING */
    }
    else {
        enemyFaction = Faction::ROBOTS;
    }
    state = PEACE;
}

World& Game::getWorld()
{
    return world;
}

void Game::spawnEnemies()
{
    enemyManager.spawn(world.getRooms(), Tile::tileSize);
}

void Game::clickLeft()
{
}

void Game::releaseLeft()
{
}

std::vector<sf::Vector2f> Game::getRelativeEnemyPositions()
{
    std::vector<sf::Vector2f> ep;
    float closest = std::numeric_limits<float>::max();
    std::vector<Enemy>& enemies = enemyManager.getEnemies();
    size_t n = enemies.size();
    for (size_t e = 0; e < n; ++e) {
        ep.push_back(enemies[e].getPosition() - player.getPosition());
        float v = scalarDistance(ep.back());
        if (v < closest) {
            closest = v;
            closestEnemyIndex = e;
        }
    }
    return ep;
}

std::vector<Enemy>& Game::getEnemies()
{
    return enemyManager.getEnemies();
}

void Game::escape()
{
    newMain(Main_State::MENU);
    player.stop();
    player.setState(Entity_State::CASTING);
    player.uncast();
}

void Game::stopInput()
{
    player.stop();
    player.uncast();
}

void Game::scroll(float delta)
{
    if (delta < 0.f) {
        view.zoom(1.5f);
    }
    else if (delta > 0.f) {
        view.zoom(0.5f);
    }
}

Game_State Game::getState()
{
    return state;
}

const Enemy& Game::getBoss()
{
    return enemyManager.getBoss();
}

Entity* Game::mousedEntity(sf::Vector2f mpos)
{
    if(player.getSprite().getGlobalBounds().contains(mpos)) {
        return &player;
    }
    else {
        std::vector<Enemy>& enemies = enemyManager.getEnemies();
        size_t n = enemies.size();
        for (size_t e = 0; e < n; e++) {
            if(enemies[e].getSprite().getGlobalBounds().contains(mpos)) {
                return &enemies[e];
            }
        }
    }

    return nullptr;
}
