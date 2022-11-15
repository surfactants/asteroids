#pragma once

#include <string>

/////////////////////////////////////////////////////////////
/// \brief
///
enum class Ability_Type {
    SHOOT,
    KNIFE,
    ROLL,
    BLINK,
    GRENADE,
    SNIPE,
    SLAM,
    CLAWS,
    NULL_TYPE
};

inline std::string abilityTypeToString(Ability_Type t)
{
    switch (t) {
        case Ability_Type::SHOOT:
            return "SHOOT";
        case Ability_Type::KNIFE:
            return "KNIFE";
        case Ability_Type::ROLL:
            return "ROLL";
        case Ability_Type::BLINK:
            return "BLINK";
        case Ability_Type::GRENADE:
            return "GRENADE";
        case Ability_Type::SNIPE:
            return "SNIPE";
        case Ability_Type::SLAM:
            return "SLAM";
        case Ability_Type::CLAWS:
            return "CLAWS";
        default:
            return "NULL_TYPE";
    }
}

inline Ability_Type stringToAbilityType(std::string s)
{
    if (s == "SHOOT")
        return Ability_Type::SHOOT;
    else if (s == "KNIFE")
        return Ability_Type::KNIFE;
    else if (s == "ROLL")
        return Ability_Type::ROLL;
    else if (s == "BLINK")
        return Ability_Type::BLINK;
    else if (s == "GRENADE")
        return Ability_Type::GRENADE;
    else if (s == "SNIPE")
        return Ability_Type::SNIPE;
    else if (s == "SLAM")
        return Ability_Type::SLAM;
    else if (s == "CLAWS")
        return Ability_Type::CLAWS;
    else
        return Ability_Type::NULL_TYPE;
}
