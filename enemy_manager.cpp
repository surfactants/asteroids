#include "enemy_manager.hpp"
#include "prng.hpp"
#include <iostream>
#include "texture_manager.hpp"

Enemy_Manager::Enemy_Manager(){
    lowLevel = 8;
    highLevel = 13;

    texture.loadFromFile("textures/entity.png");
}

void Enemy_Manager::spawn(std::vector<Room>& rooms, float tileSize){
    std::cout << "\n      spawning enemies, room count is " << rooms.size() - 1;
    for(unsigned int r = 0; r < rooms.size() - 1; ++r){
            //r should start at 1, this is for debugging
        unsigned int enemyCount = prng::number(12u, 64u);
        std::vector<sf::Vector2i> used;
        for(unsigned int e = 0; e < enemyCount; ++e){
            sf::Vector2i c = rooms[r].coordinates;
            sf::Vector2i o(0, 0);
            do{
                c -= o;
                o.x = prng::number(-rooms[r].size.x / 2, rooms[r].size.x / 2);
                o.y = prng::number(-rooms[r].size.y / 2, rooms[r].size.y / 2);
                c += o;
                for(const auto& u : used){
                    if(c == u) continue;
                }
            } while(!rooms[r].contains(c));
            Animated_Sprite sprite(texture, sf::Vector2i(64, 64));
            enemies.push_back(Enemy(sprite));
            enemies.back().setPosition(sf::Vector2f(c) * tileSize);
            enemies.back().setLevel(prng::number(lowLevel, highLevel));
            std::cout << "\n\tenemy direction set to " << enemies.back().getDirection();

            used.push_back(c);
        }
        std::cout << "\n\nENEMIES PLACED FOR ROOM " << r << ":";
        for(const auto& p : used){
            std::cout << "\n\t" << p.x << ", " << p.y;
        }
    }


    std::cout << "\n      spawning boss";
    //place boss
    Animated_Sprite sprite(texture, sf::Vector2i(128, 128));
    enemies.push_back(Enemy(sprite));
    enemies.back().setPosition(sf::Vector2f(rooms.back().coordinates) * tileSize);
    enemies.back().setLevel(highLevel + 1);
    enemies.back().setDirection(randomDirection());
}

void Enemy_Manager::clear(){
    enemies.clear();
}

void Enemy_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& enemy : enemies){
        target.draw(enemy, states);
    }
}

std::vector<Enemy>& Enemy_Manager::getEnemies(){
    return enemies;
}
