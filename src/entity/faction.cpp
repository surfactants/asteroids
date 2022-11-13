#include <entity/faction.hpp>
#include <util/prng.hpp>

std::string factionToString(Faction f)
{
    switch (f) {
    case Faction::BUGS:
        return "BUGS";
    case Faction::PIRATES:
        return "PIRATES";
    case Faction::GHOSTS:
        return "GHOSTS";
    case Faction::LITHOBIOMORPHS:
        return "LITHOBIOMORPHS";
    case Faction::ROBOTS:
        return "ROBOTS";
    case Faction::PLAYER:
        return "PLAYER_FACTION";
    default:
        return std::string();
    }
}

Faction stringToFaction(std::string s)
{
    if (s == "BUGS")
        return Faction::BUGS;
    else if (s == "PIRATES")
        return Faction::PIRATES;
    else if (s == "GHOSTS")
        return Faction::GHOSTS;
    else if (s == "LITHOBIOMORPHS")
        return Faction::LITHOBIOMORPHS;
    else if (s == "ROBOTS")
        return Faction::ROBOTS;
    else if (s == "PLAYER_FACTION")
        return Faction::PLAYER;
    else
        return Faction::NULL_FACTION;
}

Faction randomEnemyFaction()
{
    return static_cast<Faction>(prng::number(static_cast<int>(Faction::BUGS), static_cast<int>(Faction::ROBOTS)));
}
