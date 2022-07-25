#pragma once

#include <string>
#include <map>
#include <SFML/System/Vector2.hpp>
#include <entity/entity_state.hpp>

enum Faction{
    BUGS,
    PIRATES,
    GHOSTS,
    LITHOBIOMORPHS,
    ROBOTS,
    PLAYER_FACTION,
    NULL_FACTION
};

std::string factionToString(Faction f);

Faction stringToFaction(std::string s);

enum Entity_Type{
    MELEE_LIGHT,
    MELEE_HEAVY,
    RANGED,
    TURRET,
    BOSS,
    PLAYER,
    NULLENEMY
};

std::string entityTypeToString(Entity_Type e);

Entity_Type stringToEntityType(std::string s);

struct Entity_Data{
    std::string name{};
    Faction faction;
    Entity_Type type;
    sf::Vector2i size;
    std::map<Entity_State, unsigned int> aCount;
};
