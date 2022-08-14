#pragma once

struct Damage{
    int val{};

    enum Type{
        PHYSICAL,
        ENERGY,
        ACID,
        NULL_TYPE
    };

    Type type{ NULL_TYPE };

    Damage(){}
    Damage(int nval, Type ntype);
};
