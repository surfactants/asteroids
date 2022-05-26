#pragma once

#include <SFML/Graphics.hpp>

enum Direction{ LEFT, RIGHT, UP, DOWN, NULLSIDE };

/////////////////////////////////////////////////////////////
/// \brief Returns the opposite direction.
///
Direction invertDirection(const Direction direction);

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
    case LEFT:
        v.x -= distance;
        break;
    case RIGHT:
        v.x += distance;
        break;
    case UP:
        v.y -= distance;
        break;
    case DOWN:
        v.y += distance;
        break;
    default:
        break;
    }
}

/////////////////////////////////////////////////////////////
/// \brief Returns a direction relative to a given reference frame.
///
Direction normalizeDirection(const Direction ref, const Direction d);

enum Cardinal { NW, N, NE, W, E, SW, S, SE };


bool isOrthogonal(Cardinal c);

bool isDiagonal(Cardinal c);
