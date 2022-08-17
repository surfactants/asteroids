#include <entity/projectile.hpp>
#include <util/primordial.hpp>
#include <resources/texture_manager.hpp>

Projectile::Projectile(){
    type = LASER;
    speed = 10.f;
    sprite.setTexture(Texture_Manager::get("PROJECTILE"));
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f target, Projectile_Type ntype, Damage ndmg){
    float theta = calculateAngle(pos, target);
    speed = 10.f;
    sprite.setPosition(pos);
    sprite.setRotation(theta);
    calculateMoveVector(theta, speed, velocity);
    type = ntype;
    sprite.setTexture(Texture_Manager::get("PROJECTILE"));

    type = LASER;

    dmg = ndmg;
}

Projectile::Projectile(Projectile_Type ntype, Damage ndmg)
: type{ ntype }, dmg{ ndmg }{
    sprite.setTexture(Texture_Manager::get("PROJECTILE"));

    type = LASER;
}

void Projectile::setVelocity(sf::Vector2f pos, sf::Vector2f target){
    float theta = calculateAngle(pos, target);
    speed = 10.f;
    sprite.setPosition(pos);
    sprite.setRotation(theta);
    calculateMoveVector(theta, speed, velocity);
}

void Projectile::update(){
    sprite.move(velocity);
}

sf::FloatRect Projectile::getBounds(){
    return sprite.getGlobalBounds();
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
}

Projectile_Type Projectile::getType(){
    return type;
}

void Projectile::setTarget(sf::Vector2f t){
}

bool Projectile::isPlayer(){
    return player;
}

void Projectile::setPlayer(){
    player = true;
}

sf::Vector2f Projectile::getPosition(){
    return sprite.getPosition();
}

Damage Projectile::getDamage(){
    return dmg;
}
