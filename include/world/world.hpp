#pragma once

#include <SFML/Graphics.hpp>
#include <world/tile.hpp>
#include <map>
#include <world/room.hpp>
#include <entity/faction.hpp>

class World : public sf::Drawable{
public:
    World(Faction& f);
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

    void reset();

private:
    std::map<int, std::map<int, Tile*>> floor;
    std::map<int, std::map<int, Tile*>> walls;

    sf::Vector2i worldMin;
    sf::Vector2i worldMax;

    sf::Texture* textureFloors{ nullptr };
    sf::Texture* textureWalls{ nullptr };

    bool hasOrthogonalFloor(sf::Vector2i v);
    bool hasDiagonalFloor(sf::Vector2i v);

    std::map<int, std::map<int, bool>> floorMap;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Room> rooms;

    const static sf::Vector2i renderDistance;

    int getFloorX();
    int getWallX(bool n, bool s, bool w, bool e);

    Faction& enemyFaction;

};
