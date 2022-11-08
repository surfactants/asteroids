#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <map>
#include <string>

#include "action_trigger.hpp"

//this class handles conversions between
    //sf::Keyboard::Key/sf::Mouse::Button and std::string
//it is a bimap-less modification of Bromeon's solution in Thor
    //(with a hacky workaround for mouse buttons)

class Convert_Key {
public:
    Convert_Key();

    std::string toString(const Action_Trigger& key);
    Action_Trigger toKey(const std::string& str);

private:
    static std::map<sf::Keyboard::Key, std::string> to_string;
    static std::map<std::string, sf::Keyboard::Key> to_key;

    void init();
};
