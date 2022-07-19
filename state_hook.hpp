#pragma once

enum Main_State{
    MAIN_NULL,
    MAIN_MENU,
    MAIN_NEWGAME,
    MAIN_GAME,
    MAIN_LOADING,
    MAIN_QUIT
};

enum Menu_State{
    MENU_NULL,
    MENU_MAIN,
    MENU_PAUSE,
    MENU_SETTINGS
};

class State_Hook{
protected:
    static Main_State state_main;
    static Menu_State state_menu;

    static bool change_main;
    static bool change_menu;

    void newMain(Main_State ns);
    void newMenu(Menu_State ns);
};
