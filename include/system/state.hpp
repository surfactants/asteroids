#pragma once

enum class Main_State {
    MENU,
    NEWGAME,
    GAME,
    LOADING,
    QUIT,
    NULL_STATE
};

enum class Menu_State {
    MAIN,
    PAUSE,
    SETTINGS,
    KEYS,
    NULL_STATE
};
