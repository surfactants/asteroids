#pragma once

#include <string>

enum class Entity_State {
    IDLE,
    MOVING,
    ATTACKING,
    DYING,
    DEAD
};

inline std::string entityStateToString(Entity_State s)
{
    switch (s) {
    case Entity_State::IDLE:
        return "IDLE";
    case Entity_State::MOVING:
        return "MOVING";
    case Entity_State::ATTACKING:
        return "ATTACKING";
    case Entity_State::DYING:
        return "DYING";
    case Entity_State::DEAD:
        return "DEAD";
    default:
        return std::string();
    }
}
