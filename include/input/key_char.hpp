#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <map>
#include <string>

//this class handles conversions between sf::Keyboard::Key
//it is a bimap-less modification of Bromeon's solution in Thor

class Convert_Key {
public:
    Convert_Key();

    std::string toString(sf::Keyboard::Key key);
    sf::Keyboard::Key toKey(std::string str);

private:
    static std::map<sf::Keyboard::Key, std::string> to_string;
    static std::map<std::string, sf::Keyboard::Key> to_key;

    void init();
};
