#pragma once

#include <SFML/Graphics.hpp>

enum class Wall_Type{ BLANK, STRAIGHT, CORNER_OUTER, CORNER_INNER, PENINSULA, ISLAND, NULLTYPE };

class Tile : public sf::Sprite{
public:
    //Tile(){}
    const static float tileSize;
    sf::Vector2i coordinates;

    Tile(sf::Vector2i ncoord, bool nwall, sf::Texture& texture);

    bool isWall();

private:
    bool wall;
};
