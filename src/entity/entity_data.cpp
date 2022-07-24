#include <entity/entity_data.hpp>

std::string factionToString(Faction f){
    switch(f){
    case PLAYER_FACTION:
        return "PLAYER_FACTION";
    case BUGS:
        return "BUGS";
    case PIRATES:
        return "PIRATES";
    case GHOSTS:
        return "GHOSTS";
    case LITHOBIOMORPHS:
        return "LITHOBIOMORPHS";
    case ROBOTS:
        return "ROBOTS";
    default:
        return std::string();
    }
}

Faction stringToFaction(std::string s){
    if(s == "PLAYER_FACTION") return PLAYER_FACTION;
    else if(s == "BUGS") return BUGS;
    else if(s == "PIRATES") return PIRATES;
    else if(s == "GHOSTS") return GHOSTS;
    else if(s == "LITHOBIOMORPHS") return LITHOBIOMORPHS;
    else if(s == "ROBOTS") return ROBOTS;
    else return NULL_FACTION;
}

std::string entityTypeToString(Entity_Type e){
    switch(e){
    case MELEE_LIGHT:
        return "MELEE_LIGHT";
    case MELEE_HEAVY:
        return "MELEE_HEAVY";
    case RANGED:
        return "RANGED";
    case TURRET:
        return "TURRET";
    case BOSS:
        return "BOSS";
    default:
        return std::string();
    }

    return std::string();
}

Entity_Type stringToEntityType(std::string s){
    if(s == "MELEE_LIGHT") return MELEE_LIGHT;
    else if(s == "MELEE_HEAVY") return MELEE_HEAVY;
    else if(s == "RANGED") return RANGED;
    else if(s == "TURRET") return TURRET;
    else if(s == "BOSS") return BOSS;
    else return NULLENEMY;
}
