#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <string>
#include <variant>

using Action_Trigger = std::variant<sf::Keyboard::Key, sf::Mouse::Button, std::string>;

class Action {
public:
    Action(const std::string& name, const Action_Trigger& key,
        std::function<void()> press,
        std::function<void()> release)
        : name { name }
        , key { key }
        , press { press }
        , release { release }
    {}

    const std::string name;
    Action_Trigger key;
    std::function<void()> press;
    std::function<void()> release;
};
