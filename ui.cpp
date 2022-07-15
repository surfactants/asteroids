#include "ui.hpp"

UI::UI(){}

void UI::update(Game& game){
    minimap.update(game.getEnemies(), game.getPlayer().getPosition());
}

bool UI::readEvent(sf::Event& event, sf::Vector2f mPos){
    bool parsed = false;

    return parsed;
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(minimap, states);
}

void UI::scale(sf::RenderWindow& window){
    minimap.set(sf::Vector2f(window.getSize()));
}
