#pragma once

#include <util/primordial.hpp>
#include <game/game.hpp>
#include <ui/ui.hpp>
#include <menu/menu.hpp>
#include <game/loading.hpp>
#include <menu/feedback.hpp>
#include <system/input_handler.hpp>
#include <resources/font_manager.hpp>
#include <audio/audio_manager.hpp>

class Shell : public State_Hook{
public:
    Shell();
    void run();
private:
    sf::RenderWindow window;

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


    Loading_Screen loadingScreen;

    void loadNewLevel();

    void alignState();

    sf::Clock timestepClock;
    float frameTime{ 0.f };
    float targetTime{ 1.f / 60.f };
    float deltaTime{ 0.f };

    sf::Clock fpsClock;
    sf::Text fpsText;

    Sound_Interface sound_player;
    Music_Interface music_player;
};
