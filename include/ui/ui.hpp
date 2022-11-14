#pragma once

#include <SFML/Graphics.hpp>
#include <abilities/ability.hpp>
#include <game/game.hpp>
#include <ui/ui_elements.hpp>

class UI : public sf::Drawable {
public:
    UI(Game& ngame);

    void scale(sf::RenderWindow& window);

    void update();

    void clickLeft();
    void releaseLeft();

    void stopInput();

    void loadPlayerAbilities(const std::vector<Ability>& abilities);

protected:
private:
    Game& game;

    Minimap minimap;

    std::vector<Ability_Icon> playerAbilities;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
