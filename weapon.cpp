#include "weapon.hpp"
#include <iostream>

Weapon::Weapon(std::string nname, unsigned int nrange): name{ nname }, range{ nrange }{
    projectile = LASER;
    projectileSpeed = 10.f;
    cooldownThreshold = 0.4f;
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

bool Weapon::shoot(){
    float t = cooldown.getElapsedTime().asSeconds();
    std::cout << "\n\n\t" << t << " seconds since last shot";
    if(cooldown.getElapsedTime().asSeconds() >= cooldownThreshold){
        std::cout << "\n\t\tresetting at " << cooldown.restart().asSeconds();
        return true;
    }
    else return false;
}
