#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <string>
#include <variant>

class Action{
public:
    Action(const std::string& name, const std::function<void()>& function, sf::Keyboard::Key key) :
        name{ name }, function{ function }, key{ key }{}

    const std::string& name;
    const std::function<void()>& function;
    std::variant<sf::Keyboard::Key, std::string> key;
};
