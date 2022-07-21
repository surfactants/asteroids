#pragma once

#include <SFML/Window.hpp>
#include "state_hook.hpp"
#include <map>
#include <functional>
#include "menu.hpp"
#include "game.hpp"
#include "ui.hpp"

enum Mouse_Event{
    LEFT_CLICK,
    LEFT_RELEASE,
    RIGHT_CLICK,
    RIGHT_RELEASE,
    SCROLL
};

struct Input_Package{
    std::map<sf::Keyboard::Key, std::function<void()>> keyPressed;
    std::map<sf::Keyboard::Key, std::function<void()>> keyReleased;
    std::map<Mouse_Event, std::function<void()>> mouse;

    void clear();
};

class Input_Handler : public State_Hook{
public:
    Input_Handler(sf::RenderWindow& nwindow, Game& ngame, UI& nui, Menu_Package m);

    void handle();

    void menuChange();

private:
    sf::RenderWindow& window;

    sf::Event event;

    std::map<Main_State, Input_Package> context;
    std::map<Menu_State, Input_Package> context_menu;
};
