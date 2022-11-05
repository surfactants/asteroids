#pragma once

#include <SFML/Graphics.hpp>
#include <entity/faction.hpp>
#include <map>
#include <world/room.hpp>
#include <world/tile.hpp>

class World : public sf::Drawable {
public:
    World(Faction& f);

    void newLevel();

    std::map<int, std::map<int, std::unique_ptr<Floor>>>& getFloor();
    std::map<int, std::map<int, std::unique_ptr<Wall>>>& getWalls();
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
    std::map<int, std::map<int, std::unique_ptr<Wall>>> walls;
    std::map<int, std::map<int, std::unique_ptr<Floor>>> floor;

    std::map<int, std::map<int, std::unique_ptr<Detail>>> details;
    std::map<int, std::map<int, std::unique_ptr<Hazard>>> hazards;

    std::map<int, std::map<int, std::unique_ptr<Cover>>> cover;

    std::map<Faction, Hazard_Data> hazard_data;

    enum Autotile_Rules {
        AUTOMATON,
        SNAKE,
        NULLRULE
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
