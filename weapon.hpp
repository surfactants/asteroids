#pragma once

#include <SFML/Graphics.hpp>

class Weapon : public sf::Drawable{
public:
    Weapon(){}
    sf::Sprite& getSprite();
    bool getRange();

protected:
private:
    std::string name;
    unsigned int range;
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
