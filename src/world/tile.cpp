#include <world/tile.hpp>

const float Tile::tileSize = 96.f;

/////////////////////////////////////////////////////////////
Tile::Tile(sf::Vector2i ncoord, bool nwall, sf::Texture& texture) : coordinates{ ncoord }{
    setTexture(texture);

    wall = nwall;
    if(!wall){
        wallType = Wall_Type::NULLTYPE;
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

    switch(wallType){
    default:
        break;
    case Wall_Type::ISLAND:
        pos.x += size.x;
    case Wall_Type::PENINSULA:
        pos.x += size.x;
    case Wall_Type::CORNER_INNER:
        pos.x += size.x;
    case Wall_Type::CORNER_OUTER:
        pos.x += size.x;
    case Wall_Type::STRAIGHT:
        pos.x += size.x;
        break;
    }

    setTextureRect(sf::IntRect(pos, size));
}
