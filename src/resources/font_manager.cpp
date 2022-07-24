#include <resources/font_manager.hpp>
#include <system/database.hpp>

std::map<Font, sf::Font> Font_Manager::fonts = std::map<Font, sf::Font>();

Font_Manager::Font_Manager(){
    fonts = Database::getFonts();
}

sf::Font& Font_Manager::get(Font f){
    return fonts[f];
}
