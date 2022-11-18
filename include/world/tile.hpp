#pragma once

#include <SFML/Graphics.hpp>

#include <entity/damage.hpp>

/////////////////////////////////////////////////////////////
/// \brief
///
enum class Wall_Type {
    BLANK,
    STRAIGHT,
    CORNER_OUTER,
    CORNER_INNER,
    PENINSULA,
    ISLAND,
    NULL_TYPE
};

class Tile : public sf::Sprite {
public:
    //Tile(){}
    const static float tileSize;
    sf::Vector2i coordinates;

    Tile(sf::Vector2i ncoord, const sf::Texture& texture);
};

class Wall : public Tile {
public:
    Wall(sf::Vector2i ncoord, const sf::Texture& texture);
    Wall(sf::Vector2i ncoord, const sf::Texture& texture, float nprotection);
    float protection { 1.f };
};

class Cover : public Wall {
public:
    Cover(sf::Vector2i ncoord, const sf::Texture& texture, float nprotection);
};

class Floor : public Tile {
public:
    Floor(sf::Vector2i ncoord, const sf::Texture& texture);
};

class Detail : public Floor {
public:
    Detail(sf::Vector2i ncoord, const sf::Texture& texture, bool ntiled);

    bool autotiled { false };
};

class Hazard : public Detail {
public:
    Hazard(sf::Vector2i ncoord, const sf::Texture& texture, bool ntiled, Damage ndmg);
    Damage damage;
};

struct Hazard_Data {
    Damage damage;
    int index;
};

class Door : public Wall {
public:
    Door(sf::Vector2i ncoord, const sf::Texture& texture, sf::Vector2i openCoord);

    void toggle();
    void open();
    void close();

    void update();

    void setLocked(bool locked);

private:
    bool opened{ false };
    bool locked{ false };

    sf::Vector2f closePos;
    sf::Vector2f openPos;
};
