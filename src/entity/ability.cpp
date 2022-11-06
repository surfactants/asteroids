#include <entity/ability.hpp>
#include <system/database.hpp>

Ability::Ability()
{}

////////////////////////////////////////////////////////////////////////////
Ability_Icon::Ability_Icon(const Ability& ability) :
    ability{ ability }
{
}

Ability_Icon::Ability_Icon(const Ability& ability, const sf::Texture& texture, const sf::IntRect& textureRect) :
    ability{ ability }
{
    setTexture(texture);
    setTextureRect(textureRect);
}
