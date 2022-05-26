#pragma once

#include "primordial.hpp"
#include "game.hpp"
#include "ui.hpp"
#include "menu.hpp"
#include "loading.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
class Shell{
public:
    Shell();
    void run();
private:
    sf::RenderWindow window;
        sf::View viewGame;
        sf::View viewUI;
    sf::Font font;
    sf::Event event;

    Game game{ window };
    UI ui;

    void input();
    void update();
    void draw();

    sf::Text fpsText;

    Loading_Screen loadingScreen;

    enum State{ MENU, PLAYING, LOADING };

    State state;

    void loadNewLevel();
};
