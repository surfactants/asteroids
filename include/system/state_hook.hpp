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

    static Main_State prev_main;
    static Menu_State prev_menu;

    static bool change_main;
    static bool change_menu;

    static void newMain(Main_State ns);
    static void newMenu(Menu_State ns);
};
