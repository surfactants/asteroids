#include <cmath>
#include <iostream>
#include <resources/texture_manager.hpp>
#include <system/database.hpp>
#include <util/primordial.hpp>
#include <util/prng.hpp>
#include <util/vector2_stream.hpp>
#include <world/automaton.hpp>
#include <world/floor.hpp>
#include <world/world.hpp>

const sf::Vector2i World::renderDistance { 16, 10 };

World::World(Faction& f)
    : enemyFaction { f }
    , textureFloors { Texture_Manager::get("FLOOR") }
    , textureWalls { Texture_Manager::get("WALL") }
    , textureDetails { Texture_Manager::get("DETAILS") }
    , textureTiledDetail { Texture_Manager::get("TILING") }
{
    hazard_data = Database::getHazards();
}

void World::reset()
{
    std::cout << "\nresetting world...";

    floorMap.clear();
    floor.clear();
    walls.clear();
    rooms.clear();
    details.clear();
    hazards.clear();
    cover.clear();
    std::cout << "\n\tworld reset!";
}

void World::makeFloor()
{
    Floor_Generator floorGen;

    worldMin = floorGen.getWorldMin();
    worldMax = floorGen.getWorldMax();

    floorMap = floorGen.getFloorMap();

    for (const auto& x : floorGen.getFloorMap()) {
        for (const auto& y : x.second) {
            if (y.second) {
                floor[x.first][y.first] = std::make_unique<Floor>(Floor(sf::Vector2i(x.first, y.first), textureFloors));

                int tx = getFloorX();
                int ty = static_cast<int>(enemyFaction) * roundFloat(Tile::tileSize);

                sf::Vector2i tpos(tx, ty);
                sf::Vector2i tsize(roundFloat(Tile::tileSize), roundFloat(Tile::tileSize));

                floor[x.first][y.first]->setTextureRect(sf::IntRect(tpos, tsize));
            }
        }
    }

    rooms = floorGen.getRooms();

    for (const auto& room : rooms) {
        std::cout << '\n';
        for (const auto& x : room.floor) {
            std::cout << '\n';
            for (const auto& y : x.second) {
                if (y.second) {
                    std::cout << "0";
                }
                else {
                    std::cout << " ";
                }
            }
        }
    }
    std::cout << "\n\tfloor is made!";
}

void World::makeWalls()
{
    std::cout << "\nmaking walls...";
    for (int x = worldMin.x; x <= worldMax.x; ++x) {
        for (int y = worldMin.y; y <= worldMax.y; ++y) {
            if (!floorMap[x][y]) {
                sf::Vector2i v(x, y);

                bool walled = (hasOrthogonalFloor(v) || hasDiagonalFloor(v));

                if (walled) {
                    walls[x][y] = std::make_unique<Wall>(Wall(v, textureWalls));
                    bool n = !floorMap[x][y - 1],
                         s = !floorMap[x][y + 1],
                         w = !floorMap[x - 1][y],
                         e = !floorMap[x + 1][y];

                    int tx = autotileX(n, s, w, e);
                    int ty = static_cast<int>(enemyFaction) * roundFloat(Tile::tileSize);

                    sf::Vector2i tpos(tx, ty);
                    sf::Vector2i tsize(roundFloat(Tile::tileSize), roundFloat(Tile::tileSize));

                    walls[x][y]->setTextureRect(sf::IntRect(tpos, tsize));
                }
                else {
                    walls[x][y] = nullptr;
                }
            }
        }
    }
    std::cout << "\n\twalls made!";
}

void World::makeDetails()
{
    for (int x = worldMin.x; x <= worldMax.x; ++x) {
        for (int y = worldMin.y; y <= worldMax.y; ++y) {
            if (floorMap[x][y]) {
                sf::Vector2i v(x, y);
                if (prng::boolean(0.05f)) {

                    int index = prng::number(0, 4);

                    bool hazard = (hazard_data[enemyFaction].index == index);

                    int tx = prng::number(0, 4) * roundFloat(Tile::tileSize);
                    int ty = static_cast<int>(enemyFaction) * roundFloat(Tile::tileSize);

                    sf::Vector2i tpos(tx, ty);
                    sf::Vector2i tsize(roundFloat(Tile::tileSize), roundFloat(Tile::tileSize));

                    if (hazard) {
                        hazards[x][y] = std::make_unique<Hazard>(Hazard(v, textureDetails, false, hazard_data[enemyFaction].damage));
                        hazards[x][y]->setTextureRect(sf::IntRect(tpos, tsize));
                    }
                    else {
                        details[x][y] = std::make_unique<Detail>(Detail(v, textureDetails, false));
                        details[x][y]->setTextureRect(sf::IntRect(tpos, tsize));
                    }
                }
            }
        }
    }

    switch (autotile_rules[enemyFaction]) {
        case AUTOMATON:
            tileAutomata();
            break;
        case SNAKE:
            tileSnake();
            break;
        default:
            break;
    }
}

void World::tileAutomata()
{
    std::map<int, std::map<int, bool>> detailMap;

    //define faction-wise rules for the automata
    unsigned int iterations = 0;

    std::function<float(float)> t = [](float x) { return x; };
    std::function<float(float)> a = [](float x) { return x; };

    switch (enemyFaction) {
        case Faction::BUGS:
            iterations = 0;

            t = [](float x) {
                return 0.95f - sqrt(0.08f * x);
            };

            a = [](int x) {
                return sqrt(0.03f * x) + 0.01f;
            };

            break;
        case Faction::PIRATES:
            break;
        case Faction::GHOSTS:
            break;
        case Faction::LITHOBIOMORPHS:
            break;
        case Faction::ROBOTS:
            break;
        default:
            break;
    }

    for (int x = worldMin.x; x <= worldMax.x; ++x) {
        for (int y = worldMin.y; y <= worldMax.y; ++y) {
            if (floorMap[x][y]) {
                if (details[x][y] == nullptr && prng::boolean(0.05f)) {
                    detailMap[x][y] = true;
                }
                else {
                    detailMap[x][y] = false;
                }
            }
        }
    }

    Adjacency_Rules adj_take;
    Adjacency_Rules adj_add;

    for (unsigned int x = 0; x < 8; ++x) {
        adj_take[x] = t(x);
        adj_add[x] = a(x);
    }

    Automaton automaton(detailMap, iterations, adj_take, adj_add);

    detailMap = automaton.iterate();

    for (int x = worldMin.x; x <= worldMax.x; ++x) {
        for (int y = worldMin.y; y <= worldMax.y; ++y) {
            if (detailMap[x][y]) {
                sf::Vector2i v(x, y);

                int index = -1;

                bool hazard = (hazard_data[enemyFaction].index == index);

                bool n = ((walls[x][y - 1] != nullptr)
                         || ((detailMap[x][y - 1]))),

                     s = ((walls[x][y + 1] != nullptr)
                         || ((detailMap[x][y + 1]))),

                     w = ((walls[x - 1][y] != nullptr)
                         || ((detailMap[x - 1][y]))),

                     e = ((walls[x + 1][y] != nullptr)
                         || ((detailMap[x + 1][y])));

                int tx = autotileX(n, s, w, e);
                int ty = static_cast<int>(enemyFaction) * roundFloat(Tile::tileSize);

                sf::Vector2i tpos(tx, ty);
                sf::Vector2i tsize(roundFloat(Tile::tileSize), roundFloat(Tile::tileSize));

                if (hazard) {
                    hazards[x][y] = std::make_unique<Hazard>(Hazard(v, textureTiledDetail, true, hazard_data[enemyFaction].damage));
                    hazards[x][y]->setTextureRect(sf::IntRect(tpos, tsize));
                }
                else {
                    details[x][y] = std::make_unique<Detail>(Detail(v, textureTiledDetail, true));
                    details[x][y]->setTextureRect(sf::IntRect(tpos, tsize));
                }
            }
        }
    }
}

void World::tileSnake()
{
}

void World::makeHazards()
{
}

void World::makeCover()
{
}

bool World::hasOrthogonalFloor(sf::Vector2i v)
{
    return (floorMap[v.x - 1][v.y]
        || floorMap[v.x + 1][v.y]
        || floorMap[v.x][v.y - 1]
        || floorMap[v.x][v.y + 1]);
}

bool World::hasDiagonalFloor(sf::Vector2i v)
{
    return (floorMap[v.x - 1][v.y - 1]
        || floorMap[v.x + 1][v.y - 1]
        || floorMap[v.x - 1][v.y + 1]
        || floorMap[v.x + 1][v.y + 1]);
}

std::map<int, std::map<int, std::unique_ptr<Floor>>>& World::getFloor()
{
    return floor;
}

std::map<int, std::map<int, std::unique_ptr<Wall>>>& World::getWalls()
{
    return walls;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Vector2i w(target.getView().getCenter() / Tile::tileSize);

    for (int x = w.x - renderDistance.x; x <= w.x + renderDistance.x; ++x) {
        for (int y = w.y - renderDistance.y; y <= w.y + renderDistance.y; ++y) {
            if (floor.count(x) && floor.at(x).count(y) && floor.at(x).at(y) != nullptr) {
                target.draw(*floor.at(x).at(y), states);
            }
            else if (walls.count(x) && walls.at(x).count(y) && walls.at(x).at(y) != nullptr) {
                target.draw(*walls.at(x).at(y), states);
            }
            if (details.count(x) && details.at(x).count(y) && details.at(x).at(y) != nullptr) {
                target.draw(*details.at(x).at(y), states);
            }
            else if (hazards.count(x) && hazards.at(x).count(y) && hazards.at(x).at(y) != nullptr) {
                target.draw(*hazards.at(x).at(y), states);
            }
        }
    }
}

Tile* World::getWall(int x, int y)
{
    return walls[x][y].get();
}

void World::erase()
{
    rooms.clear();
    floor.clear();
    walls.clear();
}

std::vector<Room>& World::getRooms()
{
    return rooms;
}

std::vector<sf::FloatRect> World::getLocalWalls(sf::Vector2i p)
{
    std::vector<sf::FloatRect> cWalls;

    const static int depth = 1;

    for (int x = p.x - depth; x <= p.x + depth; ++x) {
        for (int y = p.y - depth; y <= p.y + depth; ++y) {
            Tile* wall = getWall(x, y);
            if (wall != nullptr) {
                cWalls.push_back(wall->getGlobalBounds());
            }
        }
    }

    return cWalls;
}

std::vector<sf::FloatRect> World::getLocalWalls(sf::Vector2f p)
{
    return getLocalWalls(sf::Vector2i(p / Tile::tileSize));
}

int World::getFloorX()
{
    return (prng::number(0, 4) * roundFloat(Tile::tileSize));
}

int World::autotileX(bool n, bool s, bool w, bool e)
{
    int sum = 0;
    if (n) {
        sum += 1;
    }
    if (w) {
        sum += 2;
    }
    if (s) {
        sum += 4;
    }
    if (e) {
        sum += 8;
    }
    return (sum * roundFloat(Tile::tileSize));
}

void World::loadAutotileRules()
{
    std::map<Faction, std::string> rules = Database::getAutotileRules();
    for (const auto& rule : rules) {
        autotile_rules[rule.first] = autotileRulesToString(rule.second);
    }
}

World::Autotile_Rules World::autotileRulesToString(std::string rule)
{
    if (rule == "AUTOMATON") {
        return AUTOMATON;
    }
    else if (rule == "SNAKE") {
        return SNAKE;
    }
    else {
        return NULL_RULE;
    }
}
