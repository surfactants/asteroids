#include <entity/ability.hpp>
#include <system/database.hpp>

Ability::Ability() { }

////////////////////////////////////////////////////////////////////////////
Ability_Icon::Ability_Icon(Ability ability, sf::Texture& texture)
    : Ability(ability)
    , setTexture(texture)
{
}
