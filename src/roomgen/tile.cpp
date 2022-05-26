#include "tile.hpp"

const sf::Vector2f Tile::tileSize = sf::Vector2f(3.f, 3.f);
const sf::Color Tile::colorFloor = sf::Color(90, 160, 90);
const sf::Color Tile::colorWall = sf::Color(50, 50, 50);

/////////////////////////////////////////////////////////////
Tile::Tile(sf::Vector2i ncoord, bool nwall) : coordinates{ ncoord }{
    setSize(tileSize);
    setOrigin(tileSize / 2.f);
    setPosition(sf::Vector2f(tileSize.x * coordinates.x, tileSize.y * coordinates.y));
    setFillColor(sf::Color::White);

    setWall(nwall);
}

/////////////////////////////////////////////////////////////
void Tile::setWall(bool nwall){
    wall = nwall;
    if(wall){
        setFillColor(colorWall);
    }
    else if(!wall){
        setFillColor(colorFloor);
    }
}

/////////////////////////////////////////////////////////////
bool& Tile::isWall(){
    return wall;
}
