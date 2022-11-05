#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <string>
#include <variant>

class Action {
public:
    Action(const std::string& name, const sf::Keyboard::Key& key,
        std::function<void()> press,
        std::function<void()> release)
        : name { name }
        , key { key }
        , press { press }
        , release { release }
    {
    }

    const std::string name;
    std::variant<sf::Keyboard::Key, std::string> key;
    std::function<void()> press;
    std::function<void()> release;
};
