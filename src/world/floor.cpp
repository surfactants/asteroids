#include <iostream>
#include <util/primordial.hpp>
#include <util/prng.hpp>
#include <util/vector2_stream.hpp>
#include <world/floor.hpp>

/////////////////////////////////////////////////////////////
Floor_Generator::Floor_Generator()
{
    reset();
}

/////////////////////////////////////////////////////////////
std::map<int, std::map<int, bool>> Floor_Generator::getFloorMap()
{
    return floorMap;
}

/////////////////////////////////////////////////////////////
void Floor_Generator::reset()
{
    do {
        static int attempt = 0;
        std::cout << "\nfloor generation attempt " << ++attempt;

        dragging = false;
        tunnels.clear();
        rooms.clear();
        floorMap.clear();

        unsigned int stepBase = 6;
        unsigned int stepCeil = 13;

        unsigned int steps = prng::number(stepBase, stepCeil);
        steps = 3;

        direction = randomOrthogonal();

        sf::Vector2i coordinates(0, 0);

        int distance = 1;

        rooms.push_back(Room(Node(coordinates), sf::Vector2i(24, 24)));
        rooms.back().type = Room::START;

        startRoom = &rooms.front();

        for (unsigned int i = 1; i <= steps; ++i) {
            std::cout << "\n  step " << i;
            while (rooms.back().contains(coordinates)) {
                std::cout << "\n\tchecking coordinates " << coordinates;
                moveDirection(coordinates, direction, distance);
            }

            std::cout << "\n\troom end found...";

            if (direction == Direction::W || direction == Direction::E) {
                coordinates.y += prng::number(-rooms.back().size.y / 2, rooms.back().size.y / 2);
            }
            else if (direction == Direction::N || direction == Direction::S) {
                coordinates.x += prng::number(-rooms.back().size.x / 2, rooms.back().size.y / 2);
            }

            std::cout << "\n\tcreating tunnel...";

            tunnels.push_back(Tunnel(coordinates, direction));

            std::cout << "\n\t\ttunnel created!";

            int roomMin = 28;
            int roomMax = 52;

            sf::Vector2i roomSize;

            if (i == steps) {
                roomSize = sf::Vector2i(64, 64);
            }
            else {
                roomSize = sf::Vector2i(prng::number(roomMin, roomMax), prng::number(roomMin, roomMax));
            }

            int offset;
            switch (direction) {
                case Direction::N:
                case Direction::S:
                    offset = roomSize.y / 2;
                    break;
                case Direction::E:
                case Direction::W:
                    offset = roomSize.x / 2;
                    break;
                default:
                    break;
            }
            moveDirection(coordinates, direction, offset);

            rooms.push_back(Room(Node(coordinates), roomSize));
            if (i < steps) {
                rooms.back().type = Room::REGULAR;
            }
        }

        endRoom = &rooms.back();
        rooms.back().type = Room::END;

        for (const auto& tunnel : tunnels) {
            if (prng::boolean(.05f)) {
                coordinates = tunnel.nodes[prng::number(tunnel.nodes.size())].coordinates;
                tunnels.push_back(Tunnel(coordinates, randomPerpendicularDirection(direction)));
            }
        }

        if (rooms.size() > 2) {
            unsigned int end = rooms.size() - 1;
            std::map<int, Direction> directions;
            for (unsigned int i = 1; i < rooms.size(); ++i) {
                if (i == end) {
                    continue;
                }
                else if (prng::boolean(1.d / (double)(stepCeil - stepBase - 2))) {
                    coordinates = rooms[i].coordinates;
                    Direction side;
                    if (i > end) {
                        side = directions[i];
                    }
                    else {
                        side = randomPerpendicularDirection(direction);
                    }

                    while (rooms[i].contains(coordinates)) {
                        moveDirection(coordinates, side, distance);
                    }

                    tunnels.push_back(Tunnel(coordinates, side));

                    sf::Vector2i roomSize(prng::number(28, 56), prng::number(28, 56));
                    int offset;
                    switch (side) {
                        case Direction::N:
                        case Direction::S:
                            offset = roomSize.y / 2;
                            break;
                        case Direction::E:
                        case Direction::W:
                            offset = roomSize.x / 2;
                            break;
                        default:
                            break;
                    }
                    moveDirection(coordinates, side, offset);
                    rooms.push_back(Room(Node(coordinates), roomSize));
                    rooms.back().type = Room::SIDE;
                    directions[rooms.size() - 1] = side;
                }
            }
        }

        worldMin = sf::Vector2i(500, 500);
        worldMax = sf::Vector2i(-500, -500);

        for (const auto& room : rooms) {
            sf::Vector2i c = room.coordinates;
            if (c.x < worldMin.x) {
                worldMin.x = c.x;
            }
            if (c.y < worldMin.y) {
                worldMin.y = c.y;
            }
            if (c.x > worldMax.x) {
                worldMax.x = c.x;
            }
            if (c.y > worldMax.y) {
                worldMax.y = c.y;
            }
        }

        worldMin -= sf::Vector2i(128, 128);
        worldMax += sf::Vector2i(128, 128);

        carveRooms();
        readRooms();
        readTunnels();
        for (unsigned int a = 0; a < 3; ++a) {
            automata();
        }

        floodCheck();
    } while (!checkRooms());

    updateRooms();

    //this loop fills in the map with false tiles
    //just in case, for creating the grid in world generation.
    for (int x = worldMin.x; x <= worldMax.x; ++x) {
        for (int y = worldMin.y; y <= worldMax.y; ++y) {
            floorMap[x][y];
        }
    }
}

/////////////////////////////////////////////////////////////
void Floor_Generator::carveRooms()
{
    bool first = true;
    for (auto& room : rooms) {
        if (first) {
            first = false;
            continue;
        }
        for (int x = room.coordinates.x - room.size.x / 2; x <= room.coordinates.x + room.size.x / 2; ++x) {
            float floorChance;
            for (int y = room.coordinates.y - room.size.y / 2; y <= room.coordinates.y + room.size.y / 2; ++y) {
                if (&room == endRoom) {
                    floorChance = .99f;
                }
                else {
                    floorChance = .9f;
                }

                float distanceFactor = calculateDistanceFactor(scalarDistance(room.coordinates, sf::Vector2i(x, y)), (room.size.x + room.size.y) / 2);

                room.floor[x][y] = prng::boolean(floorChance * distanceFactor);
            }
        }
    }
}

/////////////////////////////////////////////////////////////
void Floor_Generator::readRooms()
{
    for (const auto& room : rooms) {
        for (const auto& x : room.floor) {
            for (const auto& y : x.second) {
                floorMap[x.first][y.first] = y.second;
            }
        }
    }
}

/////////////////////////////////////////////////////////////
bool Floor_Generator::checkRooms()
{
    for (const auto& room : rooms) {
        if (!floorMap[room.coordinates.x][room.coordinates.y]) {
            return false;
        }
    }

    return true;
}

/////////////////////////////////////////////////////////////
void Floor_Generator::readTunnels()
{
    for (const auto& tunnel : tunnels) {
        for (const auto& node : tunnel.nodes) {
            addTunnelFloor(node.coordinates, prng::number(1, 3));
        }
    }
}

/////////////////////////////////////////////////////////////
void Floor_Generator::addTunnelFloor(sf::Vector2i v, int distance)
{
    floorMap[v.x][v.y] = true;
    for (int x = v.x - distance; x <= v.x + distance; ++x) {
        for (int y = v.y - distance; y <= v.y + distance; ++y) {
            floorMap[x][y] = true;
        }
    }
}

/////////////////////////////////////////////////////////////
void Floor_Generator::automata()
{
    std::map<int, std::map<int, bool>> newFloor_Generator = floorMap;

    for (auto& room : rooms) {
        sf::Vector2i c = room.coordinates;
        sf::Vector2i s = room.size;
        for (int x = c.x - s.x / 2 - 1; x <= c.x + s.x / 2 + 1; ++x) {
            for (int y = c.y - s.y / 2 - 1; y <= c.y + s.y / 2 + 1; ++y) {
                int count = countAdjacentWalls(x, y);
                if (floorMap[x][y] && count >= 4 - prng::boolean(0.4f)) {
                    newFloor_Generator[x][y] = false;
                }
                else if (!floorMap[x][y] && count <= 1) {
                    newFloor_Generator[x][y] = true;
                }
            }
        }
    }

    floorMap = newFloor_Generator;
}

/////////////////////////////////////////////////////////////
void Floor_Generator::floodCheck()
{
    std::map<int, std::map<int, bool>> floodMap;

    for (int x = worldMin.x; x < worldMax.x; ++x) {
        for (int y = worldMin.y; y < worldMax.y; ++y) {
            floodMap[x][y] = false;
        }
    }

    floodFill(rooms[0].coordinates.x, rooms[0].coordinates.y, floodMap);

    floorMap = floodMap;
}

/////////////////////////////////////////////////////////////
void Floor_Generator::floodFill(int x, int y, std::map<int, std::map<int, bool>>& floodMap)
{
    floodMap[x][y] = true;

    if (!floodMap[x - 1][y] && floorMap[x - 1][y]) {
        floodFill(x - 1, y, floodMap);
    }
    if (!floodMap[x + 1][y] && floorMap[x + 1][y]) {
        floodFill(x + 1, y, floodMap);
    }
    if (!floodMap[x][y - 1] && floorMap[x][y - 1]) {
        floodFill(x, y - 1, floodMap);
    }
    if (!floodMap[x][y + 1] && floorMap[x][y + 1]) {
        floodFill(x, y + 1, floodMap);
    }
}

/////////////////////////////////////////////////////////////
unsigned int Floor_Generator::countAdjacentWalls(int x, int y)
{
    unsigned int count = 0;

    //orthogonal count
    if (!floorMap[x - 1][y]) {
        count++;
    }
    if (!floorMap[x + 1][y]) {
        count++;
    }
    if (!floorMap[x][y - 1]) {
        count++;
    }
    if (!floorMap[x][y + 1]) {
        count++;
    }

    //diagonal count
    if (!floorMap[x - 1][y - 1]) {
        count++;
    }
    if (!floorMap[x + 1][y - 1]) {
        count++;
    }
    if (!floorMap[x - 1][y + 1]) {
        count++;
    }
    if (!floorMap[x + 1][y + 1]) {
        count++;
    }

    return count;
}

/////////////////////////////////////////////////////////////
float Floor_Generator::calculateDistanceFactor(int distance, int size)
{
    float d = distance;
    float s = size;

    float f = 1.f - (d / s) / prng::number(2.5f, 5.f);

    return f;
}

/////////////////////////////////////////////////////////////
sf::Vector2i Floor_Generator::getWorldMin()
{
    return worldMin;
}

/////////////////////////////////////////////////////////////
sf::Vector2i Floor_Generator::getWorldMax()
{
    return worldMax;
}

/////////////////////////////////////////////////////////////
std::vector<Room> Floor_Generator::getRooms()
{
    return rooms;
}

void Floor_Generator::updateRooms()
{
    for (auto& room : rooms) {
        for (int x = room.coordinates.x - room.size.x / 2; x <= room.coordinates.x + room.size.x / 2; ++x) {
            for (int y = room.coordinates.y - room.size.y / 2; y <= room.coordinates.y + room.size.y; ++y) {
                room.floor[x][y] = floorMap[x][y];
            }
        }
    }
}
