#include <entity/enemy.hpp>

#include <ai/ai.hpp>

#include <util/primordial.hpp>

#include <world/tile.hpp>

//////////////////////////////////////////////////////////////

const float Enemy::decideThreshold = 1.f;

Enemy::Enemy(Animated_Sprite nsprite)
{
    sprite = nsprite;
}

Enemy::Enemy(Entity_Data e, sf::Texture& texture)
    : Entity(e, texture)
{
    //debug:
    //resistance[Damage::ENERGY] = .9;
}

void Enemy::update()
{
    Entity::update();

    if (state == Entity_State::MOVING) {
        float distance = scalarDistance(getPosition(), moveTarget);
        if (distance < 100.f) {
            velocity = sf::Vector2f();
            setState(Entity_State::IDLE);
            //stop();
        }
    }
}

void Enemy::setMoveTarget(sf::Vector2f pos)
{
    moveTarget = pos;
    if (state != Entity_State::MOVING) {
        setState(Entity_State::MOVING);
    }

    velocity = calculateMoveVector(getPosition(), moveTarget, speed_orthogonal);

    setSpriteDirection();
}

bool Enemy::decideReady()
{
    if (decideTimer.getElapsedTime().asSeconds() >= decideThreshold) {
        decideTimer.restart();
        return true;
    }
    else {
        return false;
    }
}
