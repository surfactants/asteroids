#pragma once

#include <SFML/Graphics.hpp>
#include "state_hook.hpp"
#include <map>
#include <functional>
#include "menu.hpp"
#include "game.hpp"
#include "ui.hpp"

struct Input_Package{
    std::map<char, std::function<void()>> keyPressed;
    std::map<char, std::function<void()>> keyReleased;
    std::function<void()> left_click;
    std::function<void()> left_release;
    std::function<void()> right_click;
    std::function<void()> right_release;
};

class Input_Handler : public State_Hook{
public:
    Input_Handler(sf::RenderWindow& nwindow, Game& ngame, UI& nui, Menu* nmenu);

    void handle();

private:
    sf::RenderWindow& window;

    sf::Event event;

    std::map<Main_State, Input_Package> context;
};
