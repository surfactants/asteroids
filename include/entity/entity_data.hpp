#pragma once

#include <SFML/System/Vector2.hpp>

#include <map>
#include <string>

#include "damage.hpp"
#include "entity_state.hpp"
#include "faction.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
enum class Entity_Type {
    MELEE_LIGHT,
    MELEE_HEAVY,
    RANGED,
    TURRET,
    BOSS,
    PLAYER,
    NULL_TYPE
};

std::string entityTypeToString(Entity_Type e);

Entity_Type stringToEntityType(std::string s);

struct Entity_Data {
    std::string name;
    std::string description;
    Faction faction;
    float speed;
    Entity_Type type;
    sf::Vector2i size;
    std::map<Entity_State, unsigned int> aCount;
    std::map<Entity_State, int> aThreshold;
    std::map<Damage::Type, float> resistance;
};
