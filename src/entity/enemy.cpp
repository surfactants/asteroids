#include <entity/enemy.hpp>
#include <ai/ai.hpp>

Enemy::Enemy(Animated_Sprite nsprite){
    sprite = nsprite;
}

Enemy::Enemy(Entity_Data e, sf::Texture* texture) : Entity(e, texture){
}

void Enemy::update(){
    Entity::update();
}
