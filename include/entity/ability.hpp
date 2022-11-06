#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

class Ability {
public:
    Ability();

    enum Type {
        DAMAGE,
        UTILITY
    };
    size_t range;
    size_t magnitude;

    void startCooldown();
    bool isCooling();
    void checkCooldown();

    std::string getName() { return name; }

    size_t sheetIndex;

protected:
    float cooldownThreshold;
    sf::Clock cooldownClock;

    bool cooling{ false };

private:
    std::string name;
};

class Ability_Icon : public sf::Sprite {
public:
    Ability_Icon(const Ability& ability);
    Ability_Icon(const Ability& ability, const sf::Texture& texture, const sf::IntRect& textureRect);
private:
    const Ability& ability;
};
