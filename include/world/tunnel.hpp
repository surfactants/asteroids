#pragma once

#include <vector>

#include "direction.hpp"
#include "node.hpp"

/////////////////////////////////////////////////////////////
/// \brief Node-based tunnels for connecting rooms.
///
struct Tunnel {
    /////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// \param pos The position of the initial node.
    /// \param ndirect The primary direction of the tunnel.
    ///
    Tunnel(sf::Vector2i& pos, Direction ndirect);

    /////////////////////////////////////////////////////////////
    /// \brief The nodes defining the tunnel's shape.
    ///
    std::vector<Node> nodes;

    /////////////////////////////////////////////////////////////
    /// \brief The primary direction of the tunnel.
    ///
    Direction direction;
};
