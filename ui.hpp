#pragma once

#include <SFML/Graphics.hpp>

class UI : public sf::Drawable{
public:
    UI();

    void scale(sf::RenderWindow& window);

    bool readEvent(sf::Event& event, sf::Vector2f mPos);

protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
