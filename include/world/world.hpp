#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <memory>

#include <entity/faction.hpp>

#include "room.hpp"
#include "tile.hpp"

template <class T>
using Map_Tile = std::map<int, std::map<int, std::unique_ptr<T>>>;

//#define Map_Tile(x) std::map<int, std::map<int, std::unique_ptr<x>>>

/////////////////////////////////////////////////////////////
/// \brief
///
class World : public sf::Drawable {
public:
    World(Faction& f);

    void newLevel();

    Map_Tile<Floor>& getFloor();
    Map_Tile<Wall>& getWalls();
    Tile* getWall(int x, int y);

    void erase();
    void makeFloor();
    void makeWalls();
    void makeDetails();
    void tileAutomata();
    void tileSnake();
    void makeHazards();
    void makeCover();

    std::vector<Room>& getRooms();

    std::vector<sf::FloatRect> getLocalWalls(sf::Vector2i p);
    std::vector<sf::FloatRect> getLocalWalls(sf::Vector2f p);

    void reset();

private:
    Map_Tile<Wall> walls;
    Map_Tile<Floor> floor;

    Map_Tile<Detail> details;
    Map_Tile<Hazard> hazards;

    Map_Tile<Cover> cover;

    Map_Tile<Door> doors;

    std::map<Faction, Hazard_Data> hazard_data;

    enum Autotile_Rules {
        AUTOMATON,
        SNAKE,
        NULL_RULE
    };

    std::map<Faction, Autotile_Rules> autotile_rules;

    void loadAutotileRules();

    Autotile_Rules autotileRulesToString(std::string rule);

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
