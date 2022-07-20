#pragma once

#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include <map>
#include "room.hpp"

class World : public sf::Drawable{
public:
    World();
    ~World();

    void newLevel();

    std::map<int, std::map<int, Tile*>>& getFloor();
    std::map<int, std::map<int, Tile*>>& getWalls();
    Tile* getWall(int x, int y);

    void erase();
    void makeFloor();
    void makeWalls();

    std::vector<Room>& getRooms();

    std::vector<sf::FloatRect> getLocalWalls(sf::Vector2i p);
    std::vector<sf::FloatRect> getLocalWalls(sf::Vector2f p);

private:
    std::map<int, std::map<int, Tile*>> floor;
    std::map<int, std::map<int, Tile*>> walls;

    sf::Vector2i worldMin;
    sf::Vector2i worldMax;

    sf::Texture textureFloors;
    sf::Texture textureWalls;

    bool hasOrthogonalFloor(sf::Vector2i v);
    bool hasDiagonalFloor(sf::Vector2i v);

    std::map<int, std::map<int, bool>> floorMap;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Room> rooms;

    const static sf::Vector2i renderDistance;

};
