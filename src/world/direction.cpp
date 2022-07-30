#include <world/direction.hpp>
#include <util/prng.hpp>

std::string directionToString(Direction d){
    switch(d){
    case NORTH: return "NORTH";
    case NORTHEAST: return "NORTHEAST";
    case EAST: return "EAST";
    case SOUTHEAST: return "SOUTHEAST";
    case SOUTH: return "SOUTH";
    case SOUTHWEST: return "SOUTHWEST";
    case WEST: return "WEST";
    case NORTHWEST: return "NORTHWEST";
    default: return "NULLSIDE";
    }
}

/////////////////////////////////////////////////////////////
Direction invertDirection(const Direction d){
    if(d == NORTH) return SOUTH;
    else if(d == NORTHEAST) return SOUTHWEST;
    else if(d == EAST) return WEST;
    else if(d == SOUTHEAST) return NORTHWEST;
    else if(d == SOUTH) return NORTH;
    else if(d == SOUTHWEST) return NORTHEAST;
    else if(d == WEST) return EAST;
    else if(d == NORTHWEST) return SOUTHEAST;
    else return d;
}

Direction mirrorDirection(Direction d){
    if(d == NORTHEAST) return NORTHWEST;
    else if(d == EAST) return WEST;
    else if(d == SOUTHEAST) return SOUTHWEST;
    else if(d == SOUTHWEST) return SOUTHEAST;
    else if(d == WEST) return EAST;
    else if(d == NORTHWEST) return NORTHEAST;
    else return d;
}

/////////////////////////////////////////////////////////////
Direction randomDirection(){
    Direction d = NULLSIDE;
        d = static_cast<Direction>(prng::number(0, static_cast<int>(NORTHWEST)));
    return d;
}

/////////////////////////////////////////////////////////////
Direction randomPerpendicularDirection(Direction odirect){
    switch(odirect){
    case NORTH:
    case SOUTH:
        odirect = WEST;
        break;
    case EAST:
    case WEST:
        odirect = NORTH;
        break;
    case NORTHEAST:
    case SOUTHWEST:
        odirect = NORTHWEST;
        break;
    case NORTHWEST:
    case SOUTHEAST:
        odirect = NORTHEAST;
        break;
    default:
        odirect = NULLSIDE;
        break;
    }

    if(odirect != NULLSIDE){
        if(prng::boolean()) odirect = invertDirection(odirect);
    }

    return odirect;
}

/////////////////////////////////////////////////////////////
Direction normalizeDirection(const Direction ref, const Direction d){
    Direction r;
    switch(ref){
    case WEST:
        if(d == WEST) r = SOUTH;
        else if(d == EAST) r = NORTH;
        else if(d == NORTH) r = WEST;
        else if(d == SOUTH) r = EAST;
        break;
    case EAST:
        if(d == WEST) r = NORTH;
        else if(d == EAST) r = SOUTH;
        else if(d == NORTH) r = EAST;
        else if(d == SOUTH) r = WEST;
        break;
    case NORTH:
        r = d;
        break;
    case SOUTH:
        if(d == WEST) r = EAST;
        else if(d == EAST) r = WEST;
        else if(d == NORTH) r = SOUTH;
        else if(d == SOUTH) r = NORTH;
        break;
    default:
        r = NULLSIDE;
        break;
    } //case NORTH is excluded because Direction is already normalized to it

    return r;
}

bool isOrthogonal(Direction d){
    return (d == NORTH
         || d == WEST
         || d == EAST
         || d == SOUTH);
}

bool isDiagonal(Direction d){
    return (d == NORTHWEST
         || d == NORTHEAST
         || d == SOUTHWEST
         || d == SOUTHEAST);
}
