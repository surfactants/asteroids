#include <entity/projectile.hpp>
#include <util/primordial.hpp>

sf::Texture Projectile::texture = sf::Texture();

Projectile::Projectile(){
    type = LASER;
    speed = 10.f;
    sprite.setTexture(texture);
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f target, Projectile_Type ntype){
    float theta = calculateAngle(pos, target);
    speed = 10.f;
    sprite.setPosition(pos);
    sprite.setRotation(theta);
    calculateMoveVector(theta, speed, velocity);
    type = ntype;
    sprite.setTexture(texture);

    type = LASER;
}

void Projectile::loadTexture(){
    texture.loadFromFile("textures/bullet.png");
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
