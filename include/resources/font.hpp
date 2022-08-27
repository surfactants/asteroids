#pragma once

enum class Font{
    MENU,
    UI,
    NULLFONT
};

inline std::string fontToString(Font f){
    switch(f){
    case Font::MENU: return "MENU";
    case Font::UI: return "UI";
    default: return "";
    }
}

inline Font stringToFont(std::string s){
    if(s == "MENU"){
        return Font::MENU;
    }
    else if(s == "UI"){
        return Font::UI;
    }
    else return Font::NULLFONT;
}
