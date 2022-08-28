#include <entity/weapon.hpp>
#include <util/prng.hpp>

Weapon::Weapon(std::string nname, unsigned int nrange): name{ nname }, range{ nrange }{
    Damage dmg(prng::number(99, 101), Damage::ENERGY);
    projectile = Projectile(Projectile::LASER, dmg);
    projectileSpeed = 10.f;
    cooldownThreshold = 0.6f;
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

Projectile* Weapon::getProjectile(){
    return &projectile;
}

float Weapon::getProjectileSpeed(){
    return projectileSpeed;
}

bool Weapon::ready(){
    if(cooling && cooldown.getElapsedTime().asSeconds() >= cooldownThreshold){
        cooling = false;
    }

    return (!cooling);
}

void Weapon::startCooldown(){
    cooldown.restart();
    cooling = true;
}
