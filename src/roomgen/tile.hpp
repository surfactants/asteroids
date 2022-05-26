#pragma once

#include <SFML/Graphics.hpp>
//#include "node.hpp"

/////////////////////////////////////////////////////////////
/// \brief Deprecatable when embedded.
///
struct Tile : public sf::RectangleShape{
    const static sf::Vector2f tileSize;
        const static sf::Color colorFloor;
        const static sf::Color colorWall;
    sf::Vector2i coordinates;

    Tile(sf::Vector2i ncoord, bool nwall);

    bool wall;

    void setWall(bool nwall);
    bool& isWall();
};
