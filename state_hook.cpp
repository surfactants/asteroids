#include "state_hook.hpp"
#include <iostream>

Main_State State_Hook::state_main = MAIN_MENU;
Menu_State State_Hook::state_menu = MENU_MAIN;
bool State_Hook::change_main = true;
bool State_Hook::change_menu = true;

void State_Hook::newMain(Main_State ns){
    if(state_main != ns){
    std::cout << "\nnew main state, from " << state_menu << " to " << ns;
        state_main = ns;
        change_main = true;
    }
}

void State_Hook::newMenu(Menu_State ns){
    if(state_menu != ns){
    std::cout << "\nnew menu state, from " << state_menu << " to " << ns;
        state_menu = ns;
        change_menu = true;
    }
}
