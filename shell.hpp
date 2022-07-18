#pragma once

#include "primordial.hpp"
#include "game.hpp"
#include "ui.hpp"
#include "menu.hpp"
#include "loading.hpp"
#include "feedback.hpp"
#include "texture_manager.hpp"

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
    sf::Font font;
    sf::Event event;

    Texture_Manager textures;

    Game game{ window, viewGame };
    UI ui;
        sf::View viewUI;

    void input();
    void update();
    void draw();

    sf::Text fpsText;

    Loading_Screen loadingScreen;

    enum State{ MENU, PLAYING, LOADING };

    State state;

    void loadNewLevel();
};
