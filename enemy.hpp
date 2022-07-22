#pragma once

#include "entity.hpp"

enum Faction{
    BUGS,
    PIRATES,
    GHOSTS,
    LITHOBIOMORPHS,
    ROBOTS
};

enum Enemy_Type{
    MELEE_LIGHT,
    MELEE_HEAVY,
    RANGED,
    TURRET
};

class Enemy : public Entity{
public:
    Enemy(Animated_Sprite nsprite);

    virtual void update() override;

protected:

private:
    Faction faction;
};
