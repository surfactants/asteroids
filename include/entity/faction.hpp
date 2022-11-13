#pragma once

#include <string>

enum class Faction {
    BUGS,
    PIRATES,
    GHOSTS,
    LITHOBIOMORPHS,
    ROBOTS,
    PLAYER,
    NULL_FACTION
};

std::string factionToString(Faction f);

Faction stringToFaction(std::string s);

Faction randomEnemyFaction();
