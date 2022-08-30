#include <world/world.hpp>
#include <world/floor.hpp>
#include <util/primordial.hpp>
#include <iostream>
#include <util/vector2_stream.hpp>
#include <resources/texture_manager.hpp>
#include <util/prng.hpp>

const sf::Vector2i World::renderDistance { 16, 10 };

World::World(Faction& f)
: enemyFaction{ f }{
    textureFloors = &Texture_Manager::get("FLOOR");
    textureWalls = &Texture_Manager::get("WALL");
}

World::~World(){
    reset();
}

void World::reset(){
    std::cout << "\nresetting world...";
    for(int x = worldMin.x; x <= worldMax.x; ++x){
        for(int y = worldMin.y; y <= worldMax.y; ++y){
            if(walls[x][y] != nullptr){
                delete walls[x][y];
            }
            else if(floor[x][y] != nullptr){
                delete floor[x][y];
                floor[x][y] = nullptr;
            }
        }
    }

    floorMap.clear();
    floor.clear();
    walls.clear();
    rooms.clear();
    std::cout << "\n\tworld reset!";
}

void World::makeFloor(){
    Floor_Generator floorGen;

    worldMin = floorGen.getWorldMin();
    worldMax = floorGen.getWorldMax();

    floorMap = floorGen.getFloorMap();

    for(const auto& x : floorGen.getFloorMap()){
        for(const auto& y : x.second){
            if(y.second){
                floor[x.first][y.first] = (new Tile(sf::Vector2i(x.first, y.first), false, *textureFloors));

                int tx = getFloorX();
                int ty = static_cast<int>(enemyFaction) * roundFloat(Tile::tileSize);

                sf::Vector2i tpos(tx, ty);
                sf::Vector2i tsize(roundFloat(Tile::tileSize), roundFloat(Tile::tileSize));

                floor[x.first][y.first]->setTextureRect(sf::IntRect(tpos, tsize));
            }
        }
    }

    rooms = floorGen.getRooms();

    for(const auto& room : rooms){
            std::cout << '\n';
        for(const auto& x : room.floor){
            std::cout << '\n';
            for(const auto& y : x.second){
                if(y.second) std::cout << "0";
                else std::cout << " ";
            }
        }
    }
    std::cout << "\n\tfloor is made!";
}

void World::makeWalls(){
    std::cout << "\nmaking walls...";
    for(int x = worldMin.x; x <= worldMax.x; ++x){
        for(int y = worldMin.y; y <= worldMax.y; ++y){
            if(!floorMap[x][y]){
                sf::Vector2i v(x, y);

                bool walled = (hasOrthogonalFloor(v) || hasDiagonalFloor(v));

                if(walled){
                    walls[x][y] = new Tile(v, true, *textureWalls);
                    bool n = !floorMap[x][y - 1],
                         s = !floorMap[x][y + 1],
                         w = !floorMap[x - 1][y],
                         e = !floorMap[x + 1][y];

                    int tx = getWallX(n, s, w, e);
                    int ty = static_cast<int>(enemyFaction) * roundFloat(Tile::tileSize);

                    sf::Vector2i tpos(tx, ty);
                    sf::Vector2i tsize(roundFloat(Tile::tileSize), roundFloat(Tile::tileSize));

                    walls[x][y]->setTextureRect(sf::IntRect(tpos, tsize));
                }
                else walls[x][y] = nullptr;
            }
        }
    }
    std::cout << "\n\twalls made!";
}

bool World::hasOrthogonalFloor(sf::Vector2i v){
    return (floorMap[v.x - 1][v.y]
         || floorMap[v.x + 1][v.y]
         || floorMap[v.x][v.y - 1]
         || floorMap[v.x][v.y + 1]);
}

bool World::hasDiagonalFloor(sf::Vector2i v){
    return (floorMap[v.x - 1][v.y - 1]
         || floorMap[v.x + 1][v.y - 1]
         || floorMap[v.x - 1][v.y + 1]
         || floorMap[v.x + 1][v.y + 1]);
}

std::map<int, std::map<int, Tile*>>& World::getFloor(){
    return floor;
}

std::map<int, std::map<int, Tile*>>& World::getWalls(){
    return walls;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::Vector2i w(target.getView().getCenter() / Tile::tileSize);

    for(int x = w.x - renderDistance.x; x <= w.x + renderDistance.x; ++x){
        for(int y = w.y - renderDistance.y; y <= w.y + renderDistance.y; ++y){
            if(floor.count(x) && floor.at(x).count(y) && floor.at(x).at(y) != nullptr){
                target.draw(*floor.at(x).at(y), states);
            }
            else if(walls.count(x) && walls.at(x).count(y) && walls.at(x).at(y) != nullptr){
                target.draw(*walls.at(x).at(y), states);
            }
        }
    }
}

Tile* World::getWall(int x, int y){
    return walls[x][y];
}

void World::erase(){
    rooms.clear();
    floor.clear();
    walls.clear();
}

std::vector<Room>& World::getRooms(){
    return rooms;
}

std::vector<sf::FloatRect> World::getLocalWalls(sf::Vector2i p){
    std::vector<sf::FloatRect> cWalls;

    const static int depth = 1;

    for(int x = p.x - depth; x <= p.x + depth; ++x){
        for(int y = p.y - depth; y <= p.y + depth; ++y){
            Tile* wall = getWall(x, y);
            if(wall != nullptr){
                cWalls.push_back(wall->getGlobalBounds());
            }
        }
    }

    return cWalls;
}

std::vector<sf::FloatRect> World::getLocalWalls(sf::Vector2f p){
    return getLocalWalls(sf::Vector2i(p / Tile::tileSize));
}

int World::getFloorX(){
    return (prng::number(0, 4) * roundFloat(Tile::tileSize));
}

int World::getWallX(bool n, bool s, bool w, bool e) {
    int sum = 0;
        if (n) sum += 1;
        if (w)  sum += 2;
        if (s) sum += 4;
        if (e) sum += 8;
    return (sum * roundFloat(Tile::tileSize));
}
