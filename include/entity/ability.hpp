#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <entity/projectile.hpp>

class Ability {
public:
    Ability();

    enum Type {
        DAMAGE,
        UTILITY
    };

    Type type;

    size_t range;
    size_t magnitude;
    size_t radius;

    void startCooldown();
    bool isCooling();
    void checkCooldown();

    std::string name;

    size_t sheetIndex;

    Projectile projectile;

    float cooldown;
    float duration;

protected:
    sf::Clock cooldownClock;

    bool cooling{ false };

private:
};

class Ability_Icon : public sf::Sprite {
public:
    Ability_Icon(const Ability& ability);
    Ability_Icon(const Ability& ability, const sf::Texture& texture, const sf::IntRect& textureRect);
private:
    const Ability& ability;
};
