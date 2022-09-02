#include <world/tile.hpp>

const float Tile::tileSize = 96.f;

/////////////////////////////////////////////////////////////
Tile::Tile(sf::Vector2i ncoord, sf::Texture& texture)
: coordinates{ ncoord }{
    setTexture(texture);
    setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
    setOrigin(sf::Vector2f(tileSize / 2.f, tileSize / 2.f));
    setPosition(sf::Vector2f(coordinates) * tileSize);

}

/////////////////////////////////////////////////////////////
Wall::Wall(sf::Vector2i ncoord, sf::Texture& texture)
    : Tile{ ncoord, texture }{}

Wall::Wall(sf::Vector2i ncoord, sf::Texture& texture, float nprotection)
    : protection{ nprotection },
    Tile{ ncoord, texture }{}

/////////////////////////////////////////////////////////////
Cover::Cover(sf::Vector2i ncoord, sf::Texture& texture, float nprotection)
    : Wall{ ncoord, texture, nprotection }{}

/////////////////////////////////////////////////////////////
Floor::Floor(sf::Vector2i ncoord, sf::Texture& texture)
    : Tile{ ncoord, texture }{}

/////////////////////////////////////////////////////////////
Detail::Detail(sf::Vector2i ncoord, sf::Texture& texture, bool ntiled)
    : autotiled{ ntiled },
    Floor{ ncoord, texture }{}

/////////////////////////////////////////////////////////////
Hazard::Hazard(sf::Vector2i ncoord, sf::Texture& texture, Damage::Type ntype, bool ntiled, int ndamage)
    : type{ ntype },
    damage{ ndamage },
    Detail{ ncoord, texture, ntiled }{}
