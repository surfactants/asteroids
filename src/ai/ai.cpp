#include <ai/ai.hpp>
#include <iostream>
#include <util/primordial.hpp>

void AI::decide(Enemy& enemy, Player& player)
{
    float distance = scalarDistance(enemy.getPosition(), player.getPosition());
    if (distance <= 2500.f
        && enemy.decideReady()) {
        if (enemy.getState() == Entity_State::IDLE
            && distance >= 100.f) {
            enemy.setState(Entity_State::MOVING);
            enemy.setMoveTarget(player.getPosition());
        }
    }
}
