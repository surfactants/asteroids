#include "direction.hpp"
#include "prng.hpp"

/////////////////////////////////////////////////////////////
Direction invertDirection(const Direction direction){
    if(direction == NORTH) return SOUTH;
    else if(direction == SOUTH) return NORTH;
    else if(direction == WEST) return EAST;
    else if(direction == EAST) return WEST;
    else return NULLSIDE;
}

/////////////////////////////////////////////////////////////
Direction randomDirection(){
    return static_cast<Direction>(prng::number(0, 3));
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

bool isOrthogonal(Cardinal c){
    return (c == N
         || c == W
         || c == E
         || c == S);
}

bool isDiagonal(Cardinal c){
    return (c == NW
         || c == NE
         || c == SW
         || c == SE);
}
