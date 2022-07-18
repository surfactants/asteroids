#include "button.hpp"
Button::Button(std::string nlabel){
    label.setString(nlabel);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(container, states);
    target.draw(label, states);
}

void Button::checkMouse(sf::Vector2i mpos){
    bool contains = container.getGlobalBounds().contains(sf::Vector2f(mpos));
    if(!highlighted && contains) highlight();
    else if(highlighted && !contains) unhighlight();
}

bool Button::isHighlighted(){
    return highlighted;
}

void Button::highlight(){
    highlighted = true;
}

void Button::unhighlight(){
    highlighted = false;
}
