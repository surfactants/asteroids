#include <resources/font_manager.hpp>
#include <system/database.hpp>
#include <iostream>

std::map<Font, sf::Font> Font_Manager::fonts = std::map<Font, sf::Font>();

Font_Manager::Font_Manager(){
    std::cout << "\ninitializing font manager...\t";
    Database::getFonts(fonts);
    std::cout << "done\n";
}

sf::Font& Font_Manager::get(Font f){
    return fonts[f];
}
