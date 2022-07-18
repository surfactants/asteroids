#pragma once

#include "primordial.hpp"
#include "game.hpp"
#include "ui.hpp"
#include "menu.hpp"
#include "loading.hpp"
#include "feedback.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
class Shell : public State_Hook{
public:
    Shell();
    void run();
private:
    sf::RenderWindow window;
        sf::View viewGame;
    sf::Font font;
    sf::Event event;

    Game game{ window, viewGame };
    UI ui{ game };
        sf::View viewUI;

    void input();
    void update();
    void draw();

    sf::Text fpsText;

    Loading_Screen loadingScreen;

    void loadNewLevel();
};
