#include "room.hpp"

/////////////////////////////////////////////////////////////
Room::Room(Node node, sf::Vector2i nsize){
    coordinates = node.coordinates;
    size = nsize;
    for(int x = coordinates.x - size.x / 2; x < coordinates.x + size.x / 2; ++x){
        for(int y = coordinates.y - size.y / 2; y < coordinates.y + size.y / 2; ++y){
            floor[x][y] = true;
        }
    }
}

