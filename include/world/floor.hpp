#pragma once

#include <SFML/System/Vector2.hpp>

#include "direction.hpp"
#include "room.hpp"
#include "tile.hpp"
#include "tunnel.hpp"

/////////////////////////////////////////////////////////////
/// \brief Procedural generation of tile-based levels, consisting of rooms connected by snaking tunnels.
///
class Floor_Generator {
public:
    /////////////////////////////////////////////////////////////
    /// \brief
    ///
    Floor_Generator();

    /////////////////////////////////////////////////////////////
    /// \brief Which coordinates have floor tiles? map<int (x), map<int (y), bool>>
    ///
    std::map<int, std::map<int, bool>> getFloorMap();

    /////////////////////////////////////////////////////////////
    /// \brief Generates a new level.
    ///
    void reset();

    sf::Vector2i getWorldMin();
    sf::Vector2i getWorldMax();

    std::vector<Room> getRooms();

private:
    /////////////////////////////////////////////////////////////
    /// \brief Tracks the direction of the primary tunnel.
    ///
    Direction direction;

    /////////////////////////////////////////////////////////////
    /// \brief Node-based tunnel structures for connecting rooms.
    ///
    std::vector<Tunnel> tunnels;

    /////////////////////////////////////////////////////////////
    /// \brief Room structures representing... rooms.
    ///
    std::vector<Room> rooms;

    /////////////////////////////////////////////////////////////
    /// \brief Pointer to the final boss room.
    /// Unsafe if vector<Room> changes!!!
    ///
    Room* endRoom;

    /////////////////////////////////////////////////////////////
    /// \brief Pointer to the starting room.
    /// Unsafe if vector<Room> changes!!!
    ///
    Room* startRoom;

    /////////////////////////////////////////////////////////////
    /// \brief Tracks where floor tiles will be placed.
    ///
    std::map<int, std::map<int, bool>> floorMap;

    /////////////////////////////////////////////////////////////
    /// \brief Tracks mouse state for moving the view.
    ///
    bool dragging;

    /////////////////////////////////////////////////////////////
    /// \brief The minimum x and y dimensions of the world.
    ///
    sf::Vector2i worldMin;

    /////////////////////////////////////////////////////////////
    /// \brief The maximum x and y dimensions of the world.
    ///
    sf::Vector2i worldMax;

    /////////////////////////////////////////////////////////////
    /// \brief Randomly scatters walls in the room.
    ///
    void carveRooms();

    /////////////////////////////////////////////////////////////
    /// \brief Appends rooms to floorMap.
    ///
    void readRooms();

    /////////////////////////////////////////////////////////////
    /// \brief True if all rooms are accessible
    ///
    bool checkRooms();

    /////////////////////////////////////////////////////////////
    /// \brief Appends tunnels to floorMap.
    ///
    void readTunnels();

    /////////////////////////////////////////////////////////////
    /// \brief Sets area around tunnel nodes as floor.
    ///
    void addTunnelFloor(sf::Vector2i v, int distance);

    /////////////////////////////////////////////////////////////
    /// \brief Performs a cellular automata on the rooms.
    ///
    void automata();

    /////////////////////////////////////////////////////////////
    /// \brief Removes isolated floor areas.
    ///
    void floodCheck();

    /////////////////////////////////////////////////////////////
    /// \brief Recursive component of floodCheck()
    ///
    void floodFill(int x, int y, std::map<int, std::map<int, bool>>& floodMap);

    /////////////////////////////////////////////////////////////
    /// \brief Counts orthogonal and diagonal walls for automata.
    ///
    unsigned int countAdjacentWalls(int x, int y);

    /////////////////////////////////////////////////////////////
    /// \brief Generates a distance factor (from center) for room carving.
    ///
    float calculateDistanceFactor(int distance, int size);

    void updateRooms();
};
