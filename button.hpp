#pragma once

#include <SFML/Graphics.hpp>
#include "palette.hpp"

////////////////////////////////////////////////////////////
/// \brief Button class for mouse navigation.
///
class Button : public sf::Drawable{
public:
    Button(std::string nlabel);

    void checkMouse(sf::Vector2i mpos);
    bool isHighlighted();
    void highlight();
    void unhighlight();

private:
    sf::RectangleShape container;
    sf::Text label;

    bool highlighted = false;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
