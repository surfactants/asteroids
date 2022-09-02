#include <game/game.hpp>
#include <util/primordial.hpp>
#include <util/fmouse.hpp>
#include <system/database.hpp>
#include <util/prng.hpp>

const float Game::endThreshold = 3.f;

Game::Game(sf::RenderWindow& nwindow, sf::View& nview)
: window{ nwindow }, view{ nview }{
    player = Player(Database::getPlayerData(), Texture_Manager::get("PLAYER"));
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(world, states);
    target.draw(enemyManager, states);
    target.draw(player, states);
    target.draw(projectileManager, states);
}

void Game::update(float deltaTime){
    if(tickClock.getElapsedTime().asSeconds() >= 1.f){
        tickClock.restart();
    }

    collider.checkProjectiles(projectileManager.getProjectiles(),
                              enemyManager.getEnemies(),
                              player,
                              world);
    for(auto& enemy : enemyManager.getEnemies()){
        ai.decide(enemy, player);
        enemy.update();
        enemy.move(world.getLocalWalls(enemy.getCoordinates(Tile::tileSize)), deltaTime);
    }
    player.update();
    view.move(player.move(world.getLocalWalls(player.getCoordinates(Tile::tileSize)), deltaTime));

    if(player.isAttacking()){
        Projectile* p = player.attack(fMouse(window, view));
        if(p != nullptr){
            Projectile pf = *p;
            pf.setPlayer();
            projectileManager.create(pf);
        }
    }

    projectileManager.update(deltaTime);

    checkWin();
}

void Game::checkWin(){
    if(levelEnding){
        if(endTimer.getElapsedTime().asSeconds() >= endThreshold){
            newMain(Main_State::NEWGAME);
            stopInput();
            levelEnding = false;
        }
    }
    else if(enemyManager.checkFinalBoss()){
        levelEnding = true;
        endTimer.restart();
    }
}

Player& Game::getPlayer(){
    return player;
}

void Game::enter(){
}

void Game::newLevel(){
    player.setPosition(sf::Vector2f(0.f, 0.f));
    view.setCenter(player.getPosition());
    world.reset();
    enemyFaction = randomEnemyFaction();
    enemyFaction = Faction::BUGS; /* DEBUG / TESTING */
}

World& Game::getWorld(){
    return world;
}

void Game::spawnEnemies(){
    enemyManager.spawn(world.getRooms(), Tile::tileSize);
}

void Game::clickLeft(){
    player.setAttacking(true);
}

void Game::releaseLeft(){
    player.setAttacking(false);
}

std::vector<sf::Vector2f> Game::getEnemyPositions(){
    std::vector<sf::Vector2f> e;
    for(auto& enemy : enemyManager.getEnemies()){
        e.push_back(enemy.getPosition() - player.getPosition());
    }
    return e;
}

std::vector<Enemy>& Game::getEnemies(){
    return enemyManager.getEnemies();
}

void Game::escape(){
    newMain(Main_State::MENU);
    player.stop();
    player.setAttacking(false);
}

void Game::stopInput(){
    player.stop();
    player.setAttacking(false);
}

void Game::scroll(float delta){
    if(delta < 0.f){
        view.zoom(1.5f);
    }
    else if(delta > 0.f){
        view.zoom(0.5f);
    }
}
