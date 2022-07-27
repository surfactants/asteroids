#include <game/game.hpp>
#include <util/primordial.hpp>
#include <util/fmouse.hpp>
#include <system/database.hpp>

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

void Game::update(){
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
    }
    player.update();
    view.move(player.move(world.getLocalWalls(player.getCoordinates(Tile::tileSize))));

    if(player.isAttacking() && player.getEquippedWeapon().shoot()){
        Projectile p = player.attack(fMouse(window, view));
        p.setPlayer();
        projectileManager.create(p);
    }

    projectileManager.update();

    if(levelEnding){
        if(endTimer.getElapsedTime().asSeconds() >= endThreshold){
            newMain(MAIN_NEWGAME);
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
    newMain(MAIN_MENU);
    player.stop();
    player.setAttacking(false);
}

void Game::stopInput(){
    player.stop();
    player.setAttacking(false);
}
