#include "game.hpp"
#include <iostream>
#include "primordial.hpp"

Game::Game(sf::RenderWindow& nwindow) : window{ nwindow }{
    worldView = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));
    worldView.zoom(1.5f);

    //newLevel();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.setView(worldView);

    target.draw(world, states);

    target.draw(enemyManager, states);
    target.draw(player, states);
    //draw projectiles

}

void Game::update(sf::View& viewGame){
    if(tickClock.getElapsedTime().asSeconds() >= 1){
        player.damage(10);
        if(player.getHPCurrent() <= 0){
            player.heal(player.getHPMax());
        }
        tickClock.restart();
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

    worldView.move(viewMove);
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

    worldView.setCenter(player.getPosition());
    std::cout << "\nnew level ready!";
}

World& Game::getWorld(){
    return world;
}

void Game::spawnEnemies(){
    enemyManager.spawn(world.getRooms(), Tile::tileSize);
}

bool Game::readEvent(sf::Event& event, sf::Vector2f mPos){
    bool parsed = false;;

    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){/*
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            player.directLeft();
            std::cout << "\ndirecting left...";
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            player.directRight();
            std::cout << "\ndirecting right...";
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            player.directUp();
            std::cout << "\ndirecting up...";
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            player.directDown();
            std::cout << "\ndirecting down...";
            break;*/
        default:
            break;
        }
    }
    else if(event.type == sf::Event::KeyReleased){
        switch(event.key.code){/*
        case sf::Keyboard::Escape:
            window.close();
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            player.stopHorizontal();
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            player.stopVertical();
            break;
        case sf::Keyboard::Enter:
            enter();
            break;*/
        default:
            break;
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased){
        std::cout << "mouse release!\n";
    }

    return parsed;
}
