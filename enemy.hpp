#pragma once

#include "entity.hpp"

enum Faction{
    BUGS,
    PIRATES,
    GHOSTS,
    LITHOBIOMORPHS,
    ROBOTS
};

class Enemy : public Entity{
public:
    Enemy(){}

    virtual void update() override;

protected:

private:
    Faction faction;
};
