#include <menu/menu_elements.hpp>

Nav::Nav(std::string nlabel, sf::Font& font, Main_State ntmain, Menu_State ntmenu)
: Button{ nlabel, font }{
    target_main = ntmain;
    target_menu = ntmenu;
}

Option::Option(std::string nlabel, sf::Font& font, std::function<void()> nt)
: Button{ nlabel, font }, target{ nt }{}
