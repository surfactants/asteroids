#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Texture_Manager {
public:
    static sf::Texture& get(std::string key);

    ~Texture_Manager();

private:
    static std::map<std::string, sf::Texture> textures;
    Texture_Manager();

    static Texture_Manager* instance;
};
