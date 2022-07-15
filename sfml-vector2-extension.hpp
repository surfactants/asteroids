#include <SFML/System/Vector2.hpp>
#include <iostream>

template<typename T>
std::ostream& operator << (std::ostream& os, sf::Vector2<T> v){
    os << v.x << ", " << v.y;
    return os;
}

template<typename T>
std::istream& operator << (std::istream& is, sf::Vector2<T> v){
    is << v.x << ", " << v.y;
    return is;
}
