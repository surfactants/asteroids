#pragma once

#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable{
public:
    Menu();
protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
