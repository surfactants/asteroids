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

    std::map<int, std::map<int, Floor*>>& getFloor();
    std::map<int, std::map<int, Wall*>>& getWalls();
    Tile* getWall(int x, int y);

    void erase();
    void makeFloor();
    void makeWalls();
    void makeDetails();
    void makeTiledDetails();
    void makeHazards();
    void makeCover();

    std::vector<Room>& getRooms();

    std::vector<sf::FloatRect> getLocalWalls(sf::Vector2i p);
    std::vector<sf::FloatRect> getLocalWalls(sf::Vector2f p);

    void reset();

private:
    std::map<int, std::map<int, Wall*>> walls;
    std::map<int, std::map<int, Floor*>> floor;


    std::map<int, std::map<int, Detail*>> details;
    std::map<int, std::map<int, Hazard*>> hazards;

    std::map<int, std::map<int, Cover*>> cover;

    std::map<Faction, Hazard_Data> hazard_data;

    sf::Vector2i worldMin;
    sf::Vector2i worldMax;

    Faction& enemyFaction;

    sf::Texture& textureFloors;
    sf::Texture& textureWalls;

    sf::Texture& textureDetails;
    sf::Texture& textureTiledDetail;

    bool hasOrthogonalFloor(sf::Vector2i v);
    bool hasDiagonalFloor(sf::Vector2i v);

    std::map<int, std::map<int, bool>> floorMap;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Room> rooms;

    const static sf::Vector2i renderDistance;

    int getFloorX();
    int autotileX(bool n, bool s, bool w, bool e);
};
