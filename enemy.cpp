#include "enemy.hpp"

Enemy::Enemy(Animated_Sprite nsprite){
    sprite = nsprite;
}

void Enemy::update(){
    Entity::update();
}
