#include "game.hpp"
#include <iostream>
#include "primordial.hpp"
#include "fmouse.hpp"

Game::Game(sf::RenderWindow& nwindow, sf::View& nview)
: window{ nwindow }, view{ nview }{}

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
        enemy.update();
    }
    player.update();

    //player collision is checked here
        //TODO
            //make a discrete collision class
            //figure out how to make this faster ):
            //rework inputs to be smoother and more consistent
                //if player isn't moving in a direction and the corresponding button is pressed, they should start doing so
                    //(this happens when alternating between opposite directions)


    std::vector<sf::FloatRect> wallColliders = getPlayerCollideMap();

    sf::Vector2f viewMove = player.getVelocity();

    player.moveX();

    for(unsigned int x = 0; x < wallColliders.size(); ++x){
        if(wallColliders[x].intersects(player.getSprite().getGlobalBounds())){
            player.unmoveX();
            viewMove.x = 0.f;
            break;
        }
    }

    player.moveY();

    for(unsigned int y = 0; y < wallColliders.size(); ++y){
        if(wallColliders[y].intersects(player.getSprite().getGlobalBounds())){
            player.unmoveY();
            viewMove.y = 0.f;
            break;
        }
    }

    view.move(viewMove);

    if(player.isAttacking() && player.getEquippedWeapon().shoot()){
        Projectile p = player.attack(fMouse(window, view));
        p.setPlayer();
        projectileManager.create(p);
    }

    projectileManager.update();
}

Player& Game::getPlayer(){
    return player;
}

std::vector<sf::FloatRect> Game::getPlayerCollideMap(){
    std::vector<sf::FloatRect> wallColliders;

    sf::Vector2i p = player.getCoordinates(Tile::tileSize);

    const int depth = 1;

    for(int x = p.x - depth; x <= p.x + depth; ++x){
        for(int y = p.y - depth; y <= p.y + depth; ++y){
            Tile* wall = world.getWall(x, y);
            if(wall != nullptr){
                wallColliders.push_back(wall->getGlobalBounds());
            }
        }
    }

    return wallColliders;
}

void Game::enter(){
}

void Game::newLevel(){
    std::cout << "\ngenerating new level";

    player.setPosition(sf::Vector2f(0.f, 0.f));

    view.setCenter(player.getPosition());
    std::cout << "\nnew level ready!";
}

World& Game::getWorld(){
    return world;
}

void Game::spawnEnemies(){
    enemyManager.spawn(world.getRooms(), Tile::tileSize);
}

bool Game::readEvent(sf::Event& event, sf::Vector2f mPos){
    bool parsed = false;

    if(event.type == sf::Event::MouseButtonPressed){
        if(event.mouseButton.button == sf::Mouse::Left){
            player.setAttacking(true);
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased){
        if(event.mouseButton.button == sf::Mouse::Left){
            player.setAttacking(false);
        }
    }
    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){
        default:
            break;
        }
    }
    else if(event.type == sf::Event::KeyReleased){
        switch(event.key.code){
        default:
            break;
        }
    }

    return parsed;
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
