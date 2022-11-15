#pragma once

#include <SFML/Graphics.hpp>

#include <SFML/System/Clock.hpp>

#include <string>

#include <audio/sound.hpp>

#include "ability_type.hpp"
#include "projectile.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
class Ability {
public:
    Ability() { }

    Ability_Type type;

    size_t magnitude;
    size_t radius;

    void startCooldown();
    bool isCooling() const;
    bool checkCooldown();

    size_t sheetIndex;

    Projectile projectile;

    double cooldown;
    double duration;

    double getCooldownFractionRemaining() const;

    bool fresh { false };

    Sound_Game sound;

protected:
    sf::Clock cooldownClock;

    bool cooling { false };

private:
    double freshThreshold { 0.1d };
};

class Ability_Icon : public sf::Sprite {
public:
    Ability_Icon(const Ability& ability);
    Ability_Icon(const Ability& ability, const sf::Texture& texture, const sf::IntRect& textureRect);

    void update();

private:
    const Ability& ability;
};
