#pragma once

#include <SFML/Graphics.hpp>
#include "minimap.hpp"
#include "game.hpp"

class UI : public sf::Drawable{
public:
    UI();

    void scale(sf::RenderWindow& window);

    void update(Game& game);

    bool readEvent(sf::Event& event, sf::Vector2f mPos);

protected:
private:
    Minimap minimap;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
