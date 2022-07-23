#pragma once

#include "entity.hpp"

class Enemy : public Entity{
public:
    Enemy(){}
    Enemy(Animated_Sprite nsprite);
    Enemy(Entity_Data e, sf::Texture& texture);

    virtual void update() override;
};
