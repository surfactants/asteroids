#include <resources/texture_manager.hpp>
#include <system/database.hpp>

std::map<std::string, sf::Texture> Texture_Manager::textures = std::map<std::string, sf::Texture>();

Texture_Manager::Texture_Manager(){
    if(!loaded){
        textures.clear();

        Database::getTextures(textures);

        loaded = true;
    }
    std::cout << "done\n"
;}

sf::Texture& Texture_Manager::get(std::string key){
    if(textures.count(key)){
        return textures[key];
    }
    static sf::Texture blank;
    return blank;
}
