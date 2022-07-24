#pragma once

#include <ui/button.hpp>
#include <ui/slider.hpp>
#include <system/state_hook.hpp>

struct Nav : public Button{
    Nav(std::string nlabel, sf::Font& font, Main_State ntmain, Menu_State ntmenu);
    Main_State target_main;
    Menu_State target_menu;
};

struct Option : public Button{
    Option(std::string nlabel, sf::Font& font, std::function<void()> nt);

    std::function<void()> target;
};
