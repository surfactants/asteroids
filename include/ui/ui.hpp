#pragma once

#include <SFML/Graphics.hpp>
#include <audio/audio_manager.hpp>
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

protected:
private:
    Game& game;

    Minimap minimap;

    Audio_UI audio;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
