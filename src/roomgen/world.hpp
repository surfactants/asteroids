#pragma once

#include "node.hpp"
#include "tile.hpp"
#include "room.hpp"
#include "direction.hpp"

class World : public sf::Drawable{
public:
    World(sf::RenderWindow& window);
    void reset();

    void clickLeft(sf::Vector2i mpos);
    void releaseLeft();
    void mouseMoved(sf::Vector2i mpos);

    void floodCheck();

    void scroll(float delta);

protected:
private:

    sf::RectangleShape statusFrame;
    sf::Text status;
    sf::Font font;

    sf::View worldView;
    sf::View uiView;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Direction direction;

    std::vector<Tunnel> tunnels;

    std::vector<Room> rooms;
        Room* endRoom;
        Room* startRoom;

    sf::Vector2i mousePos;

    bool dragging;

    sf::Vector2i clickPos;

    std::vector<Tile> tiles;

    void resetVariance(int& variance, int& range);

    void addFloor();
    void addTunnelFloor(sf::Vector2i v, int distance);

    std::map<int, std::map<int, bool>> floorMap;

    void createTiles();

    void floodFill(int x, int y, std::map<int, std::map<int, bool>>& floodMap);

    unsigned int countAdjacentWalls(int x, int y);

    sf::Vector2i worldMin;
    sf::Vector2i worldMax;

    void carveRooms();

    float calculateDistanceFactor(int distance, int size);
    void automata();

    void readRooms();

    void readTunnels();

};
