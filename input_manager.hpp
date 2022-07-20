#pragma once

#include <SFML/Graphics.hpp>
#include "state_hook.hpp"
#include <map>
#include <functional>
#include "menu.hpp"
#include "game.hpp"
#include "ui.hpp"

struct Input_Package{
    std::map<std::string, std::function<void>> controls;
};

class Input_Manager : public State_Hook{
public:
    Input_Manager(sf::RenderWindow& nwindow, Game& ngame, UI& nui, Menu* nmenu);

    void update();

private:
    sf::RenderWindow& window;
    Game& game;
    UI& ui;
    Menu* menu;

    sf::Event event;

    std::map<Main_State, Input_Package> context;
};
