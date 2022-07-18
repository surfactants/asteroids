#pragma once

#include <SFML/Graphics.hpp>
#include "minimap.hpp"
#include "game.hpp"
#include "ui_elements.hpp"

class UI : public sf::Drawable{
public:
    UI(Game& ngame);

    void scale(sf::RenderWindow& window);

    void update();

    bool readEvent(sf::Event& event, sf::Vector2f mPos);

protected:
private:
    Game& game;

    Minimap minimap;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
