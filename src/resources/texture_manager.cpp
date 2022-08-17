#include <resources/texture_manager.hpp>
#include <system/database.hpp>
#include <iostream>

std::map<std::string, sf::Texture> Texture_Manager::textures = std::map<std::string, sf::Texture>();

Texture_Manager::Texture_Manager(){
    std::cout << "\ninitializing texture manager...\t";
    if(!loaded){
        textures.clear();

        Database::getTextures(textures);

        loaded = true;
    }
    std::cout << "done\n"
;}

sf::Texture& Texture_Manager::get(std::string key){
    std::cout << "\ntexture manager received request, key " << key;
    if(textures.count(key)){
        return textures[key];
    }
    static sf::Texture blank;
    return blank;
}
