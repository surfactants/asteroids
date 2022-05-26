#include "enemy_manager.hpp"
#include "prng.hpp"
#include <iostream>

Enemy_Manager::Enemy_Manager(){
    lowLevel = 8;
    highLevel = 13;
}

void Enemy_Manager::spawn(std::vector<Room>& rooms, float tileSize){
    std::cout << "\n      spawning enemies, room count is " << rooms.size() - 1;
    for(unsigned int r = 0; r < rooms.size() - 1; ++r){
            //r should start at 1, this is for debugging
        unsigned int enemyCount = prng::number(12u, 64u);
        for(unsigned int e = 0; e < enemyCount; ++e){
            std::cout << "\n         spawning in room " << r;
            sf::Vector2i c = rooms[r].coordinates;
            std::cout << "\n\t\t\tcoordinates set";
            sf::Vector2i o(0, 0);
            std::cout << "\n\t\t\toffset ... set";
            do{
                std::cout << "\n\t\t\tchecking " << c.x << ", " << c.y << " for enemy " << e << " in room " << r;
                c -= o;
                o.x = prng::number(-rooms[r].size.x / 2, rooms[r].size.x / 2);
                o.y = prng::number(-rooms[r].size.y / 2, rooms[r].size.y / 2);
                c += o;
            } while(!rooms[r].contains(c));
            std::cout << "\n\t\t\t\tlocation found";
            enemies.push_back(Enemy());
            enemies.back().setPosition(sf::Vector2f(c) * tileSize);
            enemies.back().setLevel(prng::number(lowLevel, highLevel));
        }
    }

    std::cout << "\n      spawning boss";
    //place boss
    boss.setPosition(sf::Vector2f(rooms.back().coordinates) * tileSize);
    boss.setLevel(highLevel + 1);
}

void Enemy_Manager::clear(){
    enemies.clear();
}

void Enemy_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& enemy : enemies){
        target.draw(enemy, states);
    }
}
