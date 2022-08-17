#pragma once

#include <entity/entity.hpp>

class Enemy : public Entity{
public:
    Enemy(){}
    Enemy(Animated_Sprite nsprite);
    Enemy(Entity_Data e, sf::Texture& texture);

    virtual void update() override;

    void setMoveTarget(sf::Vector2f pos);

    bool decideReady();

private:
    sf::Vector2f moveTarget;

    sf::Clock decideTimer;
    const static float decideThreshold;
};
