#pragma once

#include <SFML/Graphics.hpp>

enum class Wall_Type{ BLANK, STRAIGHT, CORNER_OUTER, CORNER_INNER, PENINSULA, ISLAND, NULLTYPE };

struct Tile : public sf::Sprite{
    Tile(){}
    const static float tileSize;
    sf::Vector2i coordinates;

    Tile(sf::Vector2i ncoord, bool nwall, sf::Texture& texture);

    bool wall;

    bool& isWall();

    void setWall(Wall_Type type);

    Wall_Type wallType;

    Tile* getWall(int x, int y);
};
