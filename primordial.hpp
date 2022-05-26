////////////////////////////////////////////////////////////
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.14159265359

/////////////////////////////////////////////////////////////
/// \brief
///
sf::Color randomColor(unsigned int alpha);

/////////////////////////////////////////////////////////////
/// \brief
///
sf::Color randomColor();

/////////////////////////////////////////////////////////////
/// \brief
///
void centerText(sf::Text& text);

sf::FloatRect getViewBounds(const sf::View& view);

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

