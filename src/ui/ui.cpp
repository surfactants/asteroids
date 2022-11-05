#include <ui/ui.hpp>

UI::UI(Game& ngame)
    : game { ngame }
{
}

void UI::update()
{
    minimap.update(game.getEnemies(), game.getPlayer().getPosition());
}

void UI::clickLeft()
{
    //if ui parses the click then return
    //else...
    game.clickLeft();
}

void UI::releaseLeft()
{
    //ui parse, NO IF; player needs to stop shooting
    game.releaseLeft();
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(minimap, states);
}

void UI::scale(sf::RenderWindow& window)
{
    minimap.set(sf::Vector2f(window.getSize()));
}

void UI::stopInput()
{
    game.stopInput();
}
