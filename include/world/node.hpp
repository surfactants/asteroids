#pragma once

#include <SFML/System/Vector2.hpp>

/////////////////////////////////////////////////////////////
/// \brief Simple coordinate-based node.
///
struct Node {
    /////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    /// \param ncoord Coordinate vector
    /// \param tileSize the size of the individual tiles
    ///
    Node(sf::Vector2i ncoord)
        : coordinates { ncoord }
    {
    }

    /////////////////////////////////////////////////////////////
    /// \brief Position in world coordinates.
    ///
    ///
    sf::Vector2i coordinates;
};
