#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <util/primordial.hpp>

namespace collide
{
    inline bool pointRect(sf::Vector2f point, sf::RectangleShape rect)
    {
        bool contains = false;

        sf::Vector2f A = rect.getPoint(0);
        sf::Vector2f B = rect.getPoint(1);
        //sf::Vector2f C = rect.getPoint(2);
        sf::Vector2f D = rect.getPoint(3);

        sf::Vector2f AP = point - A;
        sf::Vector2f AB = B - A;
        sf::Vector2f AD = D - A;

        float APAB = scalarProduct(AP, AB);
        float ABAB = scalarProduct(AB, AB);
        float APAD = scalarProduct(AP, AD);
        float ADAD = scalarProduct(AD, AD);

        if((0 < APAB) && (APAB < ABAB) && (0 < APAD) && (APAD < ADAD)){
            contains = true;
        }
        return contains;
    }
}

