#pragma once

#include <SFML/Graphics.hpp>

/////////////////////////////////////////////////////////////
/// \brief Simple coordinate-based node.
///
struct Node{
    /////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// \param ncoord Coordinate vector
    /// \param tileSize the size of the individual tiles
    ///
    Node(sf::Vector2i ncoord);

    /////////////////////////////////////////////////////////////
    /// \brief Position in world coordinates.
    ///
    ///
    sf::Vector2i coordinates;
};
