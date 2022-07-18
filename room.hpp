#pragma once

#include <map>
#include <SFML/Graphics.hpp>
#include "node.hpp"

enum Room_Type{ START, END, REGULAR, SIDE };

/////////////////////////////////////////////////////////////
/// \brief Defines rectangular room areas for carving and automating.
///
struct Room{
    /////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param node Room center node
    /// \param nsize Room size
    ///
    Room(Node node, sf::Vector2i nsize);

    /////////////////////////////////////////////////////////////
    /// \brief Holds a local floor map.
    ///
    std::map<int, std::map<int, bool>> floor;

    /////////////////////////////////////////////////////////////
    /// \brief The center of the room in world coordinates.
    ///
    sf::Vector2i coordinates;

    /////////////////////////////////////////////////////////////
    /// \brief The size of the room in world coordinates.
    ///
    sf::Vector2i size;

    /////////////////////////////////////////////////////////////
    /// \brief Checks whether a given coordinate position is in the room's floor.
    /// Careful with signs.
    ///
    template<typename T>
    bool contains(sf::Vector2<T> pos){

        return floor[(int)pos.x][(int)pos.y];
    }

    /////////////////////////////////////////////////////////////
    /// \brief Type of the room (for level population)
    ///
    Room_Type type;
};
