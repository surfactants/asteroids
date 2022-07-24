#pragma once

#include <SFML/Window.hpp>
#include <system/state_hook.hpp>
#include <map>
#include <functional>
#include <menu/menu.hpp>
#include <game/game.hpp>
#include <ui/ui.hpp>

enum Mouse_Event{
    LEFT_CLICK,
    LEFT_RELEASE,
    RIGHT_CLICK,
    RIGHT_RELEASE,
};

struct Input_Package{
    Input_Package();
    std::map<sf::Keyboard::Key, std::function<void()>> keyPressed;
    std::map<sf::Keyboard::Key, std::function<void()>> keyReleased;
    std::map<Mouse_Event, std::function<void()>> mouse;
    std::function<void(float)> scroll;

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
