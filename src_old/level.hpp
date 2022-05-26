////////////////////////////////////////////////////////////
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>

#pragma once

struct Room_Component : public sf::Drawable{
    Room_Component(sf::Texture& texture);

    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

struct Tile : public Room_Component{
    Tile(sf::Texture& texture);

    Tile* left;
    Tile* right;
    Tile* up;
    Tile* down;

    std::vector<sf::CircleShape> circles;

    void setPosition(sf::Vector2f pos);

    void setIndicators();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

struct Wall : public Room_Component{
    Wall();
};

struct Door : public Room_Component{
    Door();
};

class Room : public sf::Drawable{
public:
    Room(sf::Texture& texture);
protected:
private:
    std::vector<std::vector<Tile>> tiles;
    std::vector<Wall> walls;
    std::vector<Door> doors;
    enum Room_Type{
        CHAMBER,
        TUNNEL
    };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

struct VectorComparator{
    bool operator() (sf::Vector2i lhs, sf::Vector2i rhs) const{
        return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
    }
};

class Level : public sf::Drawable{
public:
    Level();
    void setGrid();
    const static int wsize = 512;
    void generate();
    std::vector<std::vector<sf::RectangleShape>> grid;

    void gen2();
    void gen3();

    int gen;
protected:
private:
    std::vector<Room> rooms;
    sf::Texture texture;
    std::vector<sf::RectangleShape> tiles;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::map<sf::Vector2i, bool, VectorComparator> floor;
    std::map<sf::Vector2i, bool, VectorComparator> walls;
};
