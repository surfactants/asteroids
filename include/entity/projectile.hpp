#pragma once

#include <SFML/Graphics.hpp>
#include <entity/damage.hpp>

enum Projectile_Type { BULLET, LASER };

class Projectile : public sf::Drawable{
public:
    Projectile();
    Projectile(sf::Vector2f pos, sf::Vector2f target, Projectile_Type ntype, Damage ndmg);
    Projectile(Projectile_Type ntype, Damage ndmg);

    void setVelocity(sf::Vector2f pos, sf::Vector2f target);

    void update();

    sf::FloatRect getBounds();

    Projectile_Type getType();

    void setTarget(sf::Vector2f t);

    bool isPlayer();
    void setPlayer();

    sf::Vector2f getPosition();

    Damage getDamage();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite sprite;
    sf::Vector2f velocity;
    float speed;

    Projectile_Type type;

    bool player = false;

    Damage dmg;
};
