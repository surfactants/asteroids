#pragma once

#include <string>

enum Entity_State{
    IDLE,
    MOVING,
    ATTACKING,
    DYING,
    DEAD
};

inline std::string entityStateToString(Entity_State s){
    switch(s){
    case IDLE: return "IDLE";
    case MOVING: return "MOVING";
    case ATTACKING: return "ATTACKING";
    case DYING: return "DYING";
    case DEAD: return "DEAD";
    default: return std::string();
    }
}
