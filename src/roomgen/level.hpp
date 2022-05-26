#pragma once

#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "room.hpp"
#include "tunnel.hpp"
#include "direction.hpp"

/////////////////////////////////////////////////////////////
/// \brief Procedural generation of tile-based levels, consisting of rooms connected by snaking tunnels.
///
class Level : public sf::Drawable{
public:
    /////////////////////////////////////////////////////////////
    /// \brief
    ///
    Level(sf::RenderWindow& window);

    /////////////////////////////////////////////////////////////
    /// \brief Which coordinates have floor tiles? map<int (x), map<int (y), bool>>
    ///
    std::map<int, std::map<int, bool>>& getFloorMap();

    /////////////////////////////////////////////////////////////
    /// \brief Generates a new level.
    ///
    void reset();

    /////////////////////////////////////////////////////////////
    /// \brief Triggers on mouse button press, begins screen dragging.
    ///
    void clickLeft(sf::Vector2i mpos);

    /////////////////////////////////////////////////////////////
    /// \brief  Triggers on mouse button release, ends screen dragging.
    ///
    void releaseLeft();

    /////////////////////////////////////////////////////////////
    /// \brief Triggers on mouse movement for screen dragging.
    ///
    void mouseMoved(sf::Vector2i mpos);

    /////////////////////////////////////////////////////////////
    /// \brief Triggers on mouse scroll (deprecatable in ports)
    ///
    void scroll(float delta);

private:
    /////////////////////////////////////////////////////////////
    /// \brief Deprecatable when embedded.
    ///
    sf::View worldView;

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
        ///
        Room* endRoom;

        /////////////////////////////////////////////////////////////
        /// \brief Pointer to the starting room.
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
        /// \brief Tracks mouse position to facilitate dragging.
        ///
        sf::Vector2i mousePos;

    /////////////////////////////////////////////////////////////
    /// \brief Deprecatable when embedded.
    ///
    std::vector<Tile> tiles;


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
    /// \brief Deprecatable when embedded.
    ///
    void createTiles();

    /////////////////////////////////////////////////////////////
    /// \brief Counts orthogonal and diagonal walls for automata.
    ///
    unsigned int countAdjacentWalls(int x, int y);

    /////////////////////////////////////////////////////////////
    /// \brief Generates a distance factor (from center) for room carving.
    ///
    float calculateDistanceFactor(int distance, int size);

    /////////////////////////////////////////////////////////////
    /// \brief Deprecatable when embedded (Tiling system should be different.)
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

