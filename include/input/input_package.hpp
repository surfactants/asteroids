#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <map>
#include <string>

#include "mouse_event.hpp"

struct Input_Package{
    Input_Package();
    std::map<sf::Keyboard::Key, std::function<void()>> keyPressed;
    std::map<sf::Keyboard::Key, std::function<void()>> keyReleased;
    std::map<Mouse_Event, std::function<void()>> mouse;
    std::function<void(float)> scroll;
    std::function<void()> focus_lost;

    void clear();
};
