#pragma once

#include <SFML/Graphics/Font.hpp>
#include <resources/font.hpp>

class Font_Manager{
public:
    Font_Manager();
    static sf::Font& get(Font f);

private:
    static std::map<Font, sf::Font> fonts;
};
