#pragma once

enum Main_State{
    MENU,
    GAME,
    LOADING
};

enum Menu_State{
    MAIN,
    PAUSE,
    SETTINGS
};

class State_Hook{
public:
    State_Hook();

protected:
    Main_State state_main;
    Menu_State state_menu;

private:

    readMenuStateChange();
    readMainStateChange();
};
