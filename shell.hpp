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
    sf::Font font;
    sf::Event event;

    Game game{ window, viewGame };
        sf::View viewGame;

    UI ui{ game };
        sf::View viewUI;

    Menu* menu = nullptr;
        sf::View viewMenu;
        Menu_Main menu_main;
        Menu_Pause menu_pause;
        Menu_Settings menu_settings;

    void input();
    void update();
    void draw();

    sf::Text fpsText;

    Loading_Screen loadingScreen;

    void loadNewLevel();

    void alignState();
};
