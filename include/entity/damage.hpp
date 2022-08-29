#pragma once

#include <string>

struct Damage{
    int val{};

    enum Type{
        SHARP,
        BLUNT,
        BULLET,
        ENERGY,
        ACID,
        NULL_TYPE
    };

    Type type{ NULL_TYPE };

    Damage(){}
    Damage(int nval, Type ntype);
};

inline std::string damageTypeToString(Damage::Type t){
    if(t == Damage::SHARP) return "SHARP";
    else if(t == Damage::BLUNT) return "BLUNT";
    else if(t == Damage::BULLET) return "BULLET";
    else if(t == Damage::ENERGY) return "ENERGY";
    else if(t == Damage::ACID) return "ACID";
    else return std::string("");
}

inline Damage::Type stringToDamageType(std::string s){
    if(s == "SHARP") return Damage::SHARP;
    else if(s == "BLUNT") return Damage::BLUNT;
    else if(s == "BULLET") return Damage::BULLET;
    else if(s == "ENERGY") return Damage::ENERGY;
    else if(s == "ACID") return Damage::ACID;
    else return Damage::NULL_TYPE;
}
