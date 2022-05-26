#include "world.hpp"
#include "prng.hpp"
#include <iostream>
#include <memory>
#include "primordial.hpp"

World::World(sf::RenderWindow& window){
    worldView = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));
    worldView.zoom(.2f);

    font.loadFromFile("BubblerOne-Regular.ttf");
    status.setFont(font);
    status.setFillColor(sf::Color(190, 45, 90));

    reset();
}

void World::reset(){

    worldView.setCenter(sf::Vector2f(0.f, 0.f));

    dragging = false;
    tunnels.clear();
    rooms.clear();
    tiles.clear();
    floorMap.clear();

    unsigned int stepBase = 3;
    unsigned int stepCeil = 9;

    unsigned int steps = prng::number(stepBase, stepCeil);

    direction = randomDirection();

    sf::Vector2i coordinates(0, 0);

    int distance = 1;

    rooms.push_back(Room(Node(coordinates, Tile::tileSize), sf::Vector2i(24, 24)));

    startRoom = &rooms.front();

    for(unsigned int i = 1; i <= steps; ++i){
        while(rooms.back().contains(coordinates)){
            moveDirection(coordinates, direction, distance);
        }

        if(direction == LEFT || direction == RIGHT){
            coordinates.y += prng::number(-rooms.back().size.y / 2, rooms.back().size.y / 2);
        }
        else if(direction == UP || direction == DOWN){
            coordinates.x += prng::number(-rooms.back().size.x / 2, rooms.back().size.y / 2);
        }
        else{
        }

        tunnels.push_back(Tunnel(coordinates, direction));

        int roomMin = 32;
        int roomMax = 64;

        sf::Vector2i roomSize;

        if(i == steps) roomSize = sf::Vector2i(64, 64);
        else roomSize = sf::Vector2i(prng::number(roomMin, roomMax), prng::number(roomMin, roomMax));

        int offset;
        switch(direction){
        case LEFT:
        case RIGHT:
            offset = roomSize.x / 2;
            break;
        case UP:
        case DOWN:
            offset = roomSize.y / 2;
            break;
        default:
            break;
        }
        moveDirection(coordinates, direction, offset);

        rooms.push_back(Room(Node(coordinates, Tile::tileSize), roomSize));
    }

    endRoom = &rooms.back();

    for(const auto& tunnel : tunnels){
        if(prng::boolean(.05f)){
            coordinates = tunnel.nodes[prng::number(tunnel.nodes.size())].coordinates;
            tunnels.push_back(Tunnel(coordinates, randomPerpendicularDirection(direction)));
        }
    }

    if(rooms.size() > 2){
        unsigned int end = rooms.size() - 1;
        std::map<int, Direction> directions;
        for(unsigned int i = 1; i < rooms.size(); ++i){
            if(i == end) continue;
            else if(prng::boolean(1.d / (double)(stepCeil - stepBase - 2))){
                coordinates = rooms[i].coordinates;
                Direction side;
                if(i > end) side = directions[i];
                else side = randomPerpendicularDirection(direction);

                while(rooms[i].contains(coordinates)) moveDirection(coordinates, side, distance);

                tunnels.push_back(Tunnel(coordinates, side));
                //moveDirection(coordinates, side, distance);

                sf::Vector2i roomSize(prng::number(28, 56), prng::number(28, 56));
                int offset;
                switch(side){
                case LEFT:
                case RIGHT:
                    offset = roomSize.x / 2;
                    break;
                case UP:
                case DOWN:
                    offset = roomSize.y / 2;
                    break;
                default:
                    break;
                }
                moveDirection(coordinates, side, offset);
                rooms.push_back(Room(Node(coordinates, Tile::tileSize), roomSize));
                directions[rooms.size() - 1] = side;
            }
        }
    }

    worldMin = sf::Vector2i(500, 500);
    worldMax = sf::Vector2i(-500, -500);

    for(const auto& room : rooms){
        sf::Vector2i c = room.coordinates;
        if(c.x < worldMin.x) worldMin.x = c.x;
        if(c.y < worldMin.y) worldMin.y = c.y;
        if(c.x > worldMax.x) worldMax.x = c.x;
        if(c.y > worldMax.y) worldMax.y = c.y;
    }

    worldMin -= sf::Vector2i(128, 128);
    worldMax += sf::Vector2i(128, 128);

    carveRooms();
    readRooms();
    readTunnels();
    for(unsigned int a = 0; a < 3; ++a) automata();

    floodCheck();
    createTiles();
    status.setString("New level generated.");
}

void World::resetVariance(int& variance, int& range){
    variance = prng::number(-range, range);
}

void World::readRooms(){
    for(const auto& room : rooms){
        for(const auto& x : room.floor){
            for(const auto& y : x.second){
                floorMap[x.first][y.first] = y.second;
                //tiles.push_back(Tile(sf::Vector2i(x.first, y.first), false));
            }
        }
    }
}

void World::readTunnels(){
    for(const auto& tunnel : tunnels){
        for(const auto& node : tunnel.nodes){
            addTunnelFloor(node.coordinates, prng::number(1, 3));
            //addTunnelFloor(node.coordinates, 1);
        }
    }
}

void World::addTunnelFloor(sf::Vector2i v, int distance){
    floorMap[v.x][v.y] = true;
    for(int x = v.x - distance; x <= v.x + distance; ++x){
        for(int y = v.y - distance; y <= v.y + distance; ++y){
            floorMap[x][y] = true;
        }
    }
}

void World::createTiles(){
    tiles.clear();
    for(const auto& x : floorMap){
        for(const auto& y : x.second){
            if(y.second){
                tiles.push_back(Tile(sf::Vector2i(x.first, y.first), false));
            }
        }
    }
}

float World::calculateDistanceFactor(int distance, int size){
    float d = distance;
    float s = size;

    float f = 1.f - (d / s) / prng::number(2.5f, 5.f);

    return f;
}

void World::clickLeft(sf::Vector2i mpos){
    dragging = true;
    mousePos = mpos;
}

void World::releaseLeft(){
    dragging = false;
}

void World::mouseMoved(sf::Vector2i mpos){
    if(dragging){
        worldView.move(-(mpos.x - mousePos.x) * .4f, -(mpos.y - mousePos.y) * .4f);
        mousePos = mpos;
        status.setString("dragging");
        return;
    }
    else{
        for(auto& room : rooms){
            if(room.contains(sf::Mouse::getPosition() - sf::Vector2i(worldView.getCenter()))){
                status.setString("hovering over room");
                return;
            }
        }
    }

    status.setString("");
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.setView(worldView);

    for(const auto& tile : tiles)target.draw(tile, states);
    for(const auto& tunnel : tunnels) target.draw(tunnel, states);
    for(const auto& room : rooms) target.draw(room.frame, states);

    target.setView(uiView);

    target.draw(status, states);
}

void World::automata(){
    std::map<int, std::map<int, bool>> newFloor = floorMap;

    for(auto& room : rooms){
        sf::Vector2i c = room.coordinates;
        sf::Vector2i s = room.size;
        for(int x = c.x - s.x / 2 - 1; x <= c.x + s.x / 2 + 1; ++x){
            for(int y = c.y - s.y / 2 - 1; y <= c.y + s.y / 2 + 1; ++y){
                int count = countAdjacentWalls(x, y);
                if(floorMap[x][y] && count >= 4 - prng::boolean(0.4f)) newFloor[x][y] = false;
                else if(!floorMap[x][y] && count <= 1) newFloor[x][y] = true;
            }
        }
    }

    floorMap = newFloor;
}

void World::floodCheck(){
    std::cout << "\nperforming flood check";
    std::map<int, std::map<int, bool>> floodMap;

    for(int x = worldMin.x; x < worldMax.x; ++x){
        for(int y = worldMin.y; y < worldMax.y; ++y){
            floodMap[x][y] = false;
        }
    }

    std::cout << "\n   floodMap prepared";

    floodFill(rooms[0].coordinates.x, rooms[0].coordinates.y, floodMap);

    floorMap = floodMap;

    status.setString("Flood check complete; isolated areas removed.");
}

void World::floodFill(int x, int y, std::map<int, std::map<int, bool>>& floodMap){
    //std::cout << "\n   filling tile " << x << ", " << y;
    floodMap[x][y] = true;

    //std::cout << "\n   tile " << x << ", " << y << " filled. checking orthogonal tiles";

    if(!floodMap[x - 1][y] && floorMap[x - 1][y]) floodFill(x - 1, y, floodMap);
    if(!floodMap[x + 1][y] && floorMap[x + 1][y]) floodFill(x + 1, y, floodMap);
    if(!floodMap[x][y - 1] && floorMap[x][y - 1]) floodFill(x, y - 1, floodMap);
    if(!floodMap[x][y + 1] && floorMap[x][y + 1]) floodFill(x, y + 1, floodMap);
}

unsigned int World::countAdjacentWalls(int x, int y){
    unsigned int count = 0;

    //orthogonal count
    if(!floorMap[x - 1][y]) count++;
    if(!floorMap[x + 1][y]) count++;
    if(!floorMap[x][y - 1]) count++;
    if(!floorMap[x][y + 1]) count++;

    //diagonal count
    if(!floorMap[x - 1][y - 1]) count++;
    if(!floorMap[x + 1][y - 1]) count++;
    if(!floorMap[x - 1][y + 1]) count++;
    if(!floorMap[x + 1][y + 1]) count++;

    return count;
}

void World::scroll(float delta){
    Direction direction;
    if(delta >= 0){
        direction = UP;
    }
    else if(delta <= 0){
        direction = DOWN;
    }
    else direction = NULLSIDE;

    std::cout << "\n   scroll direction: ";
    if(direction == UP){
        worldView.zoom(0.5);
    }
    else if(direction == DOWN){
        worldView.zoom(1.5);
    }
}

void World::carveRooms(){
    bool first = true;
    for(auto& room : rooms){
        if(first){
            first = false;
            continue;
        }
        for(int x = room.coordinates.x - room.size.x / 2; x <= room.coordinates.x + room.size.x / 2; ++x){
            float floorChance;
            for(int y = room.coordinates.y - room.size.y / 2; y <= room.coordinates.y + room.size.y / 2 ; ++y){
                if(&room == endRoom){
                    floorChance = .99f;
                }
                else{
                    floorChance = .9f;
                }

                float distanceFactor = calculateDistanceFactor(scalarDistance(room.coordinates, sf::Vector2i(x, y)), (room.size.x + room.size.y) / 2);

                room.floor[x][y] = prng::boolean(floorChance * distanceFactor);
            }
        }
    }
}
