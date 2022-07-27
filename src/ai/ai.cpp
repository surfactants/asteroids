#include <ai/ai.hpp>
#include <util/primordial.hpp>
#include <iostream>

void AI::decide(Enemy& enemy, Player& player){
    float distance = scalarDistance(enemy.getPosition(), player.getPosition());
    if(distance <= 2500.f
    && enemy.decideReady()){
        if(enemy.getState() == IDLE
        && distance >= 100.f){
            enemy.setState(MOVING);
            enemy.setMoveTarget(player.getPosition());
        }
    }
}
