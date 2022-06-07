#pragma once

#include <SFML/Graphics.hpp>
#include "projectile.hpp"

struct Weapon : public sf::Drawable{
public:
    Weapon(){}
    Weapon(std::string nname, unsigned int nrange);
    sf::Sprite& getSprite();
    unsigned int getRange();
    Projectile_Type getProjectile();
    float getProjectileSpeed();

protected:
private:
    std::string name;
    unsigned int range;
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Projectile_Type projectile;
    float projectileSpeed;
    bool ready;
    float cooldownThreshold; //seconds
    sf::Clock cooldown;
};
