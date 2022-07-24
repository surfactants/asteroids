#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Texture_Manager{
public:
    Texture_Manager();
    static sf::Texture* get(std::string key);

private:
    static std::map<std::string, sf::Texture> textures;

    bool loaded = false;
};
