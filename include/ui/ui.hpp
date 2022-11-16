#pragma once

#include <SFML/Graphics.hpp>

#include <abilities/ability.hpp>

#include <game/game.hpp>

#include "ui_elements.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
class UI : public sf::Drawable {
public:
    UI(Game& game);

    void scale(sf::RenderWindow& window);

    void update();

    void clickLeft();
    void releaseLeft();

    void stopInput();

    void newLevel();

    void loadPlayerAbilities(const std::vector<Ability>& abilities);

    void resize(sf::Vector2u windowSize);

private:
    Game& game;
    sf::Font& font;

    Minimap minimap;

    std::vector<Ability_Icon> playerAbilities;

    UI_Healthbar player_health;
    UI_Healthbar boss_health;

    void defineHealthbars();
    void updateHealthbars();

    //enemyInfo (mouseover)

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
