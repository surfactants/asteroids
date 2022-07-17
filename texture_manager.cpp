#include "texture_manager.hpp"

std::map<std::string, sf::Texture> Texture_Manager::textures = std::map<std::string, sf::Texture>();

void Texture_Manager::populate(){
    textures.clear();

    std::string key, path;

    key = "player";
    path = "textures/entity.png";

    textures[key].loadFromFile(path);
}

sf::Texture* Texture_Manager::get(std::string key){
    if(textures.count(key)){
        return &textures[key];
    }
    else return nullptr;
}
