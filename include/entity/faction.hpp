#pragma once

#include <string>

enum class Faction{
    BUGS,
    PIRATES,
    GHOSTS,
    LITHOBIOMORPHS,
    ROBOTS,
    PLAYER,
    NULLFACTION
};

std::string factionToString(Faction f);

Faction stringToFaction(std::string s);

Faction randomEnemyFaction();
