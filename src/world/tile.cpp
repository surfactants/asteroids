#include <world/tile.hpp>

const float Tile::tileSize = 96.f;

//////////////////////////////////////////////////////////////

Tile::Tile(sf::Vector2i ncoord, const sf::Texture& texture)
    : coordinates { ncoord }
{
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
    setOrigin(sf::Vector2f(tileSize / 2.f, tileSize / 2.f));
    setPosition(sf::Vector2f(coordinates) * tileSize);
}

//////////////////////////////////////////////////////////////

Wall::Wall(sf::Vector2i ncoord, const sf::Texture& texture)
    : Tile { ncoord, texture }
{}

Wall::Wall(sf::Vector2i ncoord, const sf::Texture& texture, float nprotection)
    : Tile { ncoord, texture }
    , protection { nprotection }
{
}

//////////////////////////////////////////////////////////////

Cover::Cover(sf::Vector2i ncoord, const sf::Texture& texture, float nprotection)
    : Wall { ncoord, texture, nprotection }
{
}

//////////////////////////////////////////////////////////////

Floor::Floor(sf::Vector2i ncoord, const sf::Texture& texture)
    : Tile { ncoord, texture }
{
}

//////////////////////////////////////////////////////////////

Detail::Detail(sf::Vector2i ncoord, const sf::Texture& texture, bool ntiled)
    : Floor { ncoord, texture }
    , autotiled { ntiled }
{
}

//////////////////////////////////////////////////////////////

Hazard::Hazard(sf::Vector2i ncoord, const sf::Texture& texture, bool ntiled, Damage ndmg)
    : Detail { ncoord, texture, ntiled }
    , damage { ndmg }
{
}

//////////////////////////////////////////////////////////////

Door::Door(sf::Vector2i ncoord, const sf::Texture& texture, sf::Vector2i openCoord) :
    Wall { ncoord, texture }, closePos{ getPosition() }, openPos{ sf::Vector2f(openCoord) * tileSize }
{
    closePos = getPosition();
    openPos = sf::Vector2f(openCoord) * tileSize;
}

void Door::open()
{
    if (!locked) {
        opened = true;
    }
}

void Door::close()
{
    if(!locked) {
        opened = false;
    }
}

void Door::toggle()
{
    if(!locked) {
        if (opened) {
            close();
        }
        else {
            open();
        }
    }
}

void Door::setLocked(bool locked)
{
    //all doors should start locked, except the first one
    //when a room is entered, the entry door should close and lock
    //when all enemies are cleared, the entry door should unlock
        //as should the next two doors (exit/entry) in all directions
    this->locked = locked;
    if (locked) {
        //set locked textureRect
    }
    else {
        //set unlocked textureRect
    }
}
