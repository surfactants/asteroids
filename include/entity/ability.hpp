#pragma once

#include <string>

class Ability {
public:
    Ability();

    enum Type { DAMAGE,
        UTILITY };
    size_t range { 0 };

protected:
private:
    std::string name;
};

class Ability_Icon : public Ability, public sf::Sprite {
public:
    Ability_Icon(Ability ability, sf::Texture& texture);
};
