#pragma once

#include <SFML/Graphics.hpp>
//#include "node.hpp"

enum Wall_Type{ BLANK, STRAIGHT, CORNER_OUTER, CORNER_INNER, PENINSULA, ISLAND, NULLTYPE };

/////////////////////////////////////////////////////////////
/// \brief Deprecatable when embedded.
///
struct Tile : public sf::Sprite{
    Tile(){}
    const static float tileSize;
    sf::Vector2i coordinates;

    Tile(sf::Vector2i ncoord, bool nwall, sf::Texture& texture);

    bool wall;

    bool& isWall();

    void setWall(Wall_Type type);

    Wall_Type wallType;

    //void rotate(float r);

    Tile* getWall(int x, int y);
};
