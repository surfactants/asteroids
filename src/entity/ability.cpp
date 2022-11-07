#include <entity/ability.hpp>
#include <system/database.hpp>

void Ability::startCooldown()
{
    cooling = true;
    cooldownClock.restart();
}

bool Ability::isCooling() const
{
    return cooling;
}

bool Ability::checkCooldown()
{
    if(cooling && cooldownClock.getElapsedTime().asSeconds() >= cooldown)
    {
        cooling = false;
    }

    return cooling;
}

double Ability::getCooldownFractionRemaining() const
{
    return cooldownClock.getElapsedTime().asSeconds() / cooldown;
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
        double percent = ability.getCooldownFractionRemaining();
        sf::Uint8 c(percent * 255);
        setColor(sf::Color(c, c, c));
    }
    else{
        //?need some sort of visual feedback indicating it's ready
    }
}
