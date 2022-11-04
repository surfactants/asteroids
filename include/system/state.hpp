#pragma once

enum class Main_State{
    MENU,
    NEWGAME,
    GAME,
    LOADING,
    QUIT,
    NULLSTATE
};

enum class Menu_State{
    MAIN,
    PAUSE,
    SETTINGS,
    KEYS,
    NULLSTATE
};
