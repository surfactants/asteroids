#pragma once

#include <SFML/Window.hpp>

#include <functional>
#include <map>

#include "action.hpp"
#include <game/game.hpp>
#include "input_package.hpp"
#include <menu/menu.hpp>
#include "mouse_event.hpp"
#include <system/state_hook.hpp>
#include <ui/ui.hpp>

class Input_Handler : public State_Hook{
public:
    Input_Handler(sf::RenderWindow& nwindow, Game& ngame, UI& nui, Menu_Package m);

    void handle();

    void menuChange();


    const std::vector<Action> getRemappableActions();

    void setRemappableActions(const std::vector<Action>& actions);

private:
    sf::RenderWindow& window;

    sf::Event event;

    std::map<Main_State, Input_Package> context;
    std::map<Menu_State, Input_Package> context_menu;
};
