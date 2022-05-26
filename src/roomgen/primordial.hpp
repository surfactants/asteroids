#pragma once

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////////////////
/// \brief Returns the scalar distance between two 2d vectors.
///
template<typename T>
T scalarDistance(const sf::Vector2<T> v, sf::Vector2<T> const w){
    T a = std::abs(w.x - v.x);
    T b = std::abs(w.y - v.y);
    return static_cast<T>(sqrt(pow(a, 2) + pow(b, 2)));
}

/////////////////////////////////////////////////////////////
/// \brief Returns the 2d vector distance between two 2d vectors.
///
template<typename T>
sf::Vector2<T> vectorDistance(const sf::Vector2<T> v, const sf::Vector2<T> w){
    return sf::Vector2<T>(w.x - v.x, w.y - v.y);
}
