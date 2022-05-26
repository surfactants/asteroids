#include "tile.hpp"
#include <iostream>

const float Tile::tileSize = 96.f;

/////////////////////////////////////////////////////////////
Tile::Tile(sf::Vector2i ncoord, bool nwall, sf::Texture& texture) : coordinates{ ncoord }{
    setTexture(texture);

    wall = nwall;
    if(!wall){
        wallType = NULLTYPE;
        setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
    }
    else if(wall){
        setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));
    }

    setOrigin(sf::Vector2f(tileSize / 2.f, tileSize / 2.f));
    setPosition(sf::Vector2f(coordinates) * tileSize);

}

/////////////////////////////////////////////////////////////
bool& Tile::isWall(){
    return wall;
}

void Tile::setWall(Wall_Type type){
    wallType = type;
    std::string wallTypes[] = { "BLANK", "STRAIGHT", "CORNER_OUTER", "CORNER_INNER", "PENINSULA", "ISLAND", "NULLTYPE" };

    sf::Vector2i pos(0, 0);
    sf::Vector2i size(96, 96);

    //std::cout << "\n      wall type is " << wallTypes[(int)type];

    switch(wallType){
    default:
        break;
    case ISLAND:
        pos.x += size.x;
    case PENINSULA:
        pos.x += size.x;
    case CORNER_INNER:
        pos.x += size.x;
    case CORNER_OUTER:
        pos.x += size.x;
    case STRAIGHT:
        pos.x += size.x;
        break;
    }

    //std::cout << "\n      wall texture x pos = " << pos.x;

    setTextureRect(sf::IntRect(pos, size));
}
