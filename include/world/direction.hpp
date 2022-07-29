#pragma once

#include <SFML/Graphics.hpp>

enum Direction{
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
    SOUTH,
    SOUTHWEST,
    WEST,
    NORTHWEST,
    NULLSIDE
};

std::string directionToString(Direction d);

/////////////////////////////////////////////////////////////
/// \brief Returns the opposite direction.
///
Direction invertDirection(const Direction direction);

Direction mirrorDirection(Direction d);

/////////////////////////////////////////////////////////////
/// \brief Returns a random direction.
///
Direction randomDirection();

/////////////////////////////////////////////////////////////
/// \brief Returns a random direction perpendicular to odirect.
///
Direction randomPerpendicularDirection(Direction odirect);

/////////////////////////////////////////////////////////////
/// \brief Increments a vector depending on direction.
///
template<typename T>
void moveDirection(sf::Vector2<T>& v, const Direction direction, const T distance){
    switch(direction){
    case NORTH:
        v.y -= distance;
        break;
    case SOUTH:
        v.y += distance;
        break;
    case EAST:
        v.x += distance;
        break;
    case WEST:
        v.x -= distance;
        break;
    default:
        break;
    }
}

/////////////////////////////////////////////////////////////
/// \brief Returns a direction relative to a given reference frame.
///
Direction normalizeDirection(const Direction ref, const Direction d);

bool isOrthogonal(Direction d);

bool isDiagonal(Direction d);

//enum Cardinal { NW, N, NE, W, E, SW, S, SE };

