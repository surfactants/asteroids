#include "texture_manager.hpp"
#include "database.hpp"
#include <iostream>

std::map<std::string, sf::Texture> Texture_Manager::textures = std::map<std::string, sf::Texture>();

Texture_Manager::Texture_Manager(){
    if(!loaded){
        textures.clear();

        Database::getTextures(textures);

        std::cout << "\ntextures loaded:";
        for(const auto& t : textures){
            std::cout << "\n\t" << t.first;
        }
    }
/*
    std::string key, path;

    key = "player";
    path = "textures/player.png";

    textures[key].loadFromFile(path);

    key = "enemy";
    path = "textures/enemy.png";

    textures[key].loadFromFile(path);

    key = "boss";
    path = "textures/boss.png";

    textures[key].loadFromFile(path);*/
}

sf::Texture* Texture_Manager::get(std::string key){
    if(textures.count(key)){
        return &textures[key];
    }
    else return nullptr;
}
