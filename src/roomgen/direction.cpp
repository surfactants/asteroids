#include "direction.hpp"
#include "prng.hpp"

/////////////////////////////////////////////////////////////
Direction invertDirection(const Direction direction){
    if(direction == LEFT) return RIGHT;
    else if(direction == RIGHT) return LEFT;
    else if(direction == UP) return DOWN;
    else if(direction == DOWN) return UP;
    else return NULLSIDE;
}

/////////////////////////////////////////////////////////////
Direction randomDirection(){
    return static_cast<Direction>(prng::number(0, 3));
}

/////////////////////////////////////////////////////////////
Direction randomPerpendicularDirection(Direction odirect){
    switch(odirect){
    case LEFT:
    case RIGHT:
        odirect = UP;
        break;
    case UP:
    case DOWN:
        odirect = LEFT;
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
    case LEFT:
        if(d == LEFT) r = DOWN;
        else if(d == RIGHT) r = UP;
        else if(d == UP) r = LEFT;
        else if(d == DOWN) r = RIGHT;
        break;
    case RIGHT:
        if(d == LEFT) r = UP;
        else if(d == RIGHT) r = DOWN;
        else if(d == UP) r = RIGHT;
        else if(d == DOWN) r = LEFT;
        break;
    case UP:
        r = d;
        break;
    case DOWN:
        if(d == LEFT) r = RIGHT;
        else if(d == RIGHT) r = LEFT;
        else if(d == UP) r = DOWN;
        else if(d == DOWN) r = UP;
        break;
    default:
        r = NULLSIDE;
        break;
    } //case UP is excluded because Direction is already normalized to it

    return r;
}
