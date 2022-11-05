#pragma once

#include <SFML/Graphics.hpp>
#include <entity/damage.hpp>

class Projectile : public sf::Drawable {
public:
    enum Type { BULLET,
        LASER };

    Projectile();
    Projectile(sf::Vector2f pos, sf::Vector2f target, Type ntype, Damage ndmg);
    Projectile(Type ntype, Damage ndmg);

    void setVelocity(sf::Vector2f pos, sf::Vector2f target);

    void update(float deltaTime);

    sf::FloatRect getBounds();

    Type getType();

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

    Type type;

    bool player = false;

    Damage dmg;
};
