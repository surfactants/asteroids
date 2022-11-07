#include <entity/ability.hpp>
#include <system/database.hpp>

void Ability::startCooldown()
{
    cooling = true;
    cooldownClock.restart();
}

bool Ability::isCooling()
{
    return checkCooldown();
}

bool Ability::checkCooldown()
{
    if(cooldownClock.getElapsedTime().asSeconds() >= cooldown)
    {
        cooling = false;
    }

    return cooling;
}

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

void Ability_Icon::update()
{
    if(ability.isCooling()){
        //calculate overlay
    }
    else{
        //???
    }
}
