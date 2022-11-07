#pragma once

#include <string>

struct Damage {
    size_t val {};

    enum Type {
        SHARP,
        BLUNT,
        BULLET,
        ACID,
        EXPLOSIVE,
        FIRE,
        PLASMA,
        LASER,
        ELECTRIC,
        NULL_TYPE
    };

    Type type { NULL_TYPE };

    Damage() { }
    Damage(size_t val, Type type);
};

inline std::string damageTypeToString(Damage::Type t)
{
    if (t == Damage::SHARP)
        return "SHARP";
    else if (t == Damage::BLUNT)
        return "BLUNT";
    else if (t == Damage::BULLET)
        return "BULLET";
    else if (t == Damage::ACID)
        return "ACID";
    else if (t == Damage::EXPLOSIVE)
        return "EXPLOSIVE";
    else if (t == Damage::FIRE)
        return "FIRE";
    else if (t == Damage::PLASMA)
        return "PLASMA";
    else if (t == Damage::LASER)
        return "LASER";
    else if (t == Damage::ELECTRIC)
        return "ELECTRIC";
    else
        return std::string("NULL_TYPE");
}

inline Damage::Type stringToDamageType(std::string s)
{
    if (s == "SHARP")
        return Damage::SHARP;
    else if (s == "BLUNT")
        return Damage::BLUNT;
    else if (s == "BULLET")
        return Damage::BULLET;
    else if (s == "ACID")
        return Damage::ACID;
    else if (s == "EXPLOSIVE")
        return Damage::EXPLOSIVE;
    else if (s == "FIRE")
        return Damage::FIRE;
    else if (s == "PLASMA")
        return Damage::PLASMA;
    else if (s == "LASER")
        return Damage::LASER;
    else if (s == "ELECTRIC")
        return Damage::ELECTRIC;
    else
        return Damage::NULL_TYPE;
}
