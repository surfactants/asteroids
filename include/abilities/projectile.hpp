#pragma once

#include <SFML/Graphics.hpp>
#include <entity/damage.hpp>
#include "ability_type.hpp"

class Projectile : public sf::Drawable {
public:
    Projectile(){}
    Projectile(Ability_Type type, double speed, Damage dmg, double range);

    void setVelocity(sf::Vector2f pos, sf::Vector2f target);

    void update(float deltaTime);

    sf::FloatRect getBounds();

    Ability_Type getType();

    void setTarget(sf::Vector2f t);

    bool isPlayer();
    void setPlayer();

    sf::Vector2f getPosition();

    Damage getDamage();

    double distanceTraveled{ 0.f };

    bool inRange();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite sprite;
    sf::Vector2f velocity;

    Ability_Type type;

    double speed;

    bool player = false;

    Damage dmg;

    double range;

    void loadTexture();
};
