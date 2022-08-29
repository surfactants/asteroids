#pragma once

#include <string>
#include <map>
#include <SFML/System/Vector2.hpp>
#include <entity/entity_state.hpp>
#include <entity/faction.hpp>
#include <entity/damage.hpp>

enum class Entity_Type{
    MELEE_LIGHT,
    MELEE_HEAVY,
    RANGED,
    TURRET,
    BOSS,
    PLAYER,
    NULLTYPE
};

std::string entityTypeToString(Entity_Type e);

Entity_Type stringToEntityType(std::string s);

struct Entity_Data{
    std::string name{};
    Faction faction;
    float speed;
    Entity_Type type;
    sf::Vector2i size;
    std::map<Entity_State, unsigned int> aCount;
    std::map<Entity_State, int> aThreshold;
    std::map<Damage::Type, float> resistance;
};
