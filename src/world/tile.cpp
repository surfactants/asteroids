#include <world/tile.hpp>

const float Tile::tileSize = 96.f;

/////////////////////////////////////////////////////////////
Tile::Tile(sf::Vector2i ncoord, bool nwall, sf::Texture& texture)
: coordinates{ ncoord }, wall{ nwall }{
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
    setOrigin(sf::Vector2f(tileSize / 2.f, tileSize / 2.f));
    setPosition(sf::Vector2f(coordinates) * tileSize);

}

/////////////////////////////////////////////////////////////
bool Tile::isWall(){
    return wall;
}
