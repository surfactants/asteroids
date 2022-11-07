#include <entity/projectile.hpp>
#include <resources/texture_manager.hpp>
#include <util/primordial.hpp>

Projectile::Projectile(Ability_Type type, double speed, Damage dmg, size_t range) :
    type{ type }, speed{ speed }, dmg{ dmg }
{
    loadTexture();
}

void Projectile::setVelocity(sf::Vector2f pos, sf::Vector2f target)
{
    float theta = calculateAngle(pos, target);
    sprite.setPosition(pos);
    sprite.setRotation(theta);
    calculateMoveVector(theta, speed, velocity);
}

void Projectile::loadTexture()
{
    sprite.setTexture(Texture_Manager::get("PROJECTILES"));
    sf::Vector2i rpos(0, 0);
        rpos.x += 12 * static_cast<unsigned int>(type);
    sf::Vector2i rsize(12, 16);
    sprite.setTextureRect(sf::IntRect(rpos, rsize));
}

void Projectile::update(float deltaTime)
{
    sf::Vector2f offset = velocity * deltaTime;
    sprite.move(offset);
    distanceTraveled += scalarDistance(offset);
}

sf::FloatRect Projectile::getBounds()
{
    return sprite.getGlobalBounds();
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

Ability_Type Projectile::getType()
{
    return type;
}

void Projectile::setTarget(sf::Vector2f t)
{
}

bool Projectile::inRange()
{
    return (distanceTraveled < range);
}

bool Projectile::isPlayer()
{
    return player;
}

void Projectile::setPlayer()
{
    player = true;
}

sf::Vector2f Projectile::getPosition()
{
    return sprite.getPosition();
}

Damage Projectile::getDamage()
{
    return dmg;
}
