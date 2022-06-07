#include "weapon.hpp"

Weapon::Weapon(std::string nname, unsigned int nrange): name{ nname }, range{ nrange }{
    projectile = LASER;
    projectileSpeed = 10.f;
}

sf::Sprite& Weapon::getSprite(){
    return sprite;
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

unsigned int Weapon::getRange(){
    return range;
}

Projectile_Type Weapon::getProjectile(){
    return projectile;
}

float Weapon::getProjectileSpeed(){
    return projectileSpeed;
}
