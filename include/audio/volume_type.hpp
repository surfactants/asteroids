#pragma once

#include <string>

enum Volume_Type{
    VOL_MUSIC,
    VOL_GAME,
    VOL_UI,
    VOL_NULL
};

inline std::string volumeTypeToString(Volume_Type t){
    switch(t){
    case VOL_MUSIC: return "VOL_MUSIC";
    case VOL_GAME: return "VOL_GAME";
    case VOL_UI: return "VOL_UI";
    default: return std::string();
    }
}

inline Volume_Type stringToVolumeType(std::string s){
    if(s == "VOL_MUSIC") return VOL_MUSIC;
    else if(s == "VOL_GAME") return VOL_GAME;
    else if(s == "VOL_UI") return VOL_UI;
    else return VOL_NULL;
}
