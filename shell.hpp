#pragma once

#include "primordial.hpp"
#include "game.hpp"
#include "ui.hpp"
#include "menu.hpp"
#include "loading.hpp"
#include "feedback.hpp"
#include "input_handler.hpp"

class Shell : public State_Hook{
public:
    Shell();
    void run();
private:
    Texture_Manager texureManager; //solely used for instancing, don't use this.
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

    //Input_Handler input{ window, game, ui };
    Input_Handler input{ window, game, ui, Menu_Package(&menu_main, &menu_pause, &menu_settings) };

    void update();
    void draw();

    sf::Text fpsText;

    Loading_Screen loadingScreen;

    void loadNewLevel();

    void alignState();
};
