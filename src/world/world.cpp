#include <world/world.hpp>
#include <world/floor.hpp>
#include <util/primordial.hpp>
#include <iostream>

const sf::Vector2i World::renderDistance { 16, 10 };

World::World(){
    textureFloors.loadFromFile("textures/floors.png");
    textureWalls.loadFromFile("textures/walls.png");
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
    std::cout << "\nmaking floor...";
    Floor_Generator floorGen;

    worldMin = floorGen.getWorldMin();
    worldMax = floorGen.getWorldMax();

    floorMap = floorGen.getFloorMap();

    for(const auto& x : floorGen.getFloorMap()){
        for(const auto& y : x.second){
            if(y.second){
                floor[x.first][y.first] = (new Tile(sf::Vector2i(x.first, y.first), false, textureFloors));
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

                bool adjFloor[8] = {
                   floorMap[x - 1][y - 1],
                   floorMap[x + 0][y - 1],
                   floorMap[x + 1][y - 1],
                   floorMap[x - 1][y + 0],
                   floorMap[x + 1][y + 0],
                   floorMap[x - 1][y + 1],
                   floorMap[x + 0][y + 1],
                   floorMap[x + 1][y + 1]
                };

                if(std::find(std::begin(adjFloor), std::end(adjFloor), true) != std::end(adjFloor)){
                    //std::cout << "\n\n   setting wall " << x << ", " << y << "...";
                    walls[x][y] = new Tile(v, true, textureWalls);

                    static bool first = true;
                    if(first){
                        walls[x][y]->setColor(sf::Color::Green);
                        first = false;
                    }

                    Wall_Type type = BLANK;

                    unsigned int floorCount = std::count(std::begin(adjFloor), std::end(adjFloor), true);

                    std::string failure = "\n   a wall failed to set properly: ";

                    float rotation = 0.f;

                    std::string cardinalTypes[] = { "NW", "N", "NE", "W", "E", "SW", "S", "SE" };

                    if(floorCount == 0){
                        //std::cout << failure << "floorCount == 0";
                        type = BLANK;
                    }
                    else if(floorCount == 1){
                        Cardinal cdirect = static_cast<Cardinal>((int)(std::distance(std::begin(adjFloor), std::find(std::begin(adjFloor), std::end(adjFloor), true))));
                        if(cdirect == N || cdirect == W || cdirect == E || cdirect == S){
                            type = STRAIGHT;

                            switch(cdirect){
                            case N:
                                rotation = 180.f;
                                break;
                            case W:
                                rotation = 90.f;
                                break;
                            case E:
                                rotation = 270.f;
                                break;
                            default:
                                break;
                            }
                        }
                        else if(cdirect == NW || cdirect == NE || cdirect == SW || cdirect == SE){
                            type = CORNER_INNER;

                            switch(cdirect){
                            case NW:
                                rotation = 90.f;
                                break;
                            case NE:
                                rotation = 180.f;
                                break;
                            case SE:
                                rotation = 270.f;
                                break;
                            default:
                                break;
                            }
                        }
                        //else std::cout << failure << "1 was counted, but no cardinal direction was found for a wall with 1 adjacent wall!";
                    }
                    else if(floorCount == 2){
                        Cardinal c[2];
                            unsigned int d = 0;
                            for(unsigned int i = 0; i < sizeof(adjFloor); ++i){
                                if(adjFloor[i]) c[d++] = static_cast<Cardinal>(i);
                            }

                            //std::cout << "\n   floorCount == 2: cardinal sizes { " << cardinalTypes[(int)c[0]] << ", " << cardinalTypes[(int)c[1]] << " }";

                        for(unsigned int i = 0; i < 2; ++i){
                            unsigned int j = 1 - i;
                            if((c[i] == N && c[j] == NW)
                            || (c[i] == N && c[j] == NE)){
                                type = STRAIGHT;
                                rotation = 180.f;
                            }
                            else if((c[i] == W && c[j] == NW)
                                 || (c[i] == W && c[j] == SW)){
                                type = STRAIGHT;
                                rotation = 90.f;
                            }
                            else if((c[i] == E && c[j] == NE)
                                 || (c[i] == E && c[j] == SE)){
                                type = STRAIGHT;
                                rotation = 270.f;
                            }
                            else if((c[i] == S && c[j] == SW)
                                 || (c[i] == S && c[j] == SE)){
                                type = STRAIGHT;
                                break;
                            }
                        }
                    }
                    //else std::cout << failure << " floorCount of " << floorCount;

                    walls[x][y]->setWall(type);
                    walls[x][y]->rotate(rotation);
                }
                else{
                    walls[x][y] = nullptr;
                }
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
