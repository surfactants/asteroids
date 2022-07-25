#pragma once

#include <util/primordial.hpp>
#include <game/game.hpp>
#include <ui/ui.hpp>
#include <menu/menu.hpp>
#include <game/loading.hpp>
#include <menu/feedback.hpp>
#include <system/input_handler.hpp>
#include <resources/font_manager.hpp>

class Shell : public State_Hook{
public:
    Shell();
    void run();
private:
    Texture_Manager texureManager; //instancing
    Font_Manager fontManager; //instancing

    sf::RenderWindow window;
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
