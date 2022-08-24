#include <entity/entity_data.hpp>

std::string entityTypeToString(Entity_Type e){
    switch(e){
    case Entity_Type::MELEE_LIGHT:
        return "MELEE_LIGHT";
    case Entity_Type::MELEE_HEAVY:
        return "MELEE_HEAVY";
    case Entity_Type::RANGED:
        return "RANGED";
    case Entity_Type::TURRET:
        return "TURRET";
    case Entity_Type::BOSS:
        return "BOSS";
    default:
        return std::string();
    }

    return std::string();
}

Entity_Type stringToEntityType(std::string s){
    if(s == "MELEE_LIGHT") return Entity_Type::MELEE_LIGHT;
    else if(s == "MELEE_HEAVY") return Entity_Type::MELEE_HEAVY;
    else if(s == "RANGED") return Entity_Type::RANGED;
    else if(s == "TURRET") return Entity_Type::TURRET;
    else if(s == "BOSS") return Entity_Type::BOSS;
    else return Entity_Type::NULLTYPE;
}
