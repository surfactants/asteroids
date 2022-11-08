#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include <string>

#include "action_trigger.hpp"

class Action {
public:
    Action(const std::string& name, const Action_Trigger& trigger,
        std::function<void()> press,
        std::function<void()> release)
        : name { name }
        , trigger { trigger }
        , press { press }
        , release { release }
    {}

    const std::string name;
    Action_Trigger trigger;
    std::function<void()> press;
    std::function<void()> release;
};
