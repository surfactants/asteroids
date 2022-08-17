#pragma once

enum Font{
    FONT_MENU,
    FONT_UI,
    FONT_NULL
};

inline std::string fontToString(Font f){
    switch(f){
    case FONT_MENU: return "FONT_MENU";
    case FONT_UI: return "FONT_UI";
    default: return "";
    }
}

inline Font stringToFont(std::string s){
    if(s == "FONT_MENU" || s == "MENU"){
        return FONT_MENU;
    }
    else if(s == "FONT_UI" || s == "UI"){
        return FONT_UI;
    }
    else return FONT_NULL;
}
