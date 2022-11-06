#pragma once

#include <SFML/Graphics.hpp>
#include <animation/animated_sprite.hpp>
#include <entity/damage.hpp>
#include <entity/entity_data.hpp>
#include <entity/weapon.hpp>
#include <vector>
#include <world/direction.hpp>
#include "ability.hpp"

#define ABILITY_COUNT 4

/////////////////////////////////////////////////////////////
/// \brief
///
class Entity : public sf::Drawable {
public:
    Entity() { }
    Entity(Entity_Data& e, sf::Texture& texture);
    //Entity(const Entity& e);

    sf::Vector2f getPosition();

    int getHPCurrent();
    int getHPMax();

    unsigned int getLevel();

    void takeDamage(Damage dmg);
    void heal(int val);

    void setState(Entity_State nstate);

    virtual void update();

    void stop();

    void setPosition(sf::Vector2f pos);

    sf::Vector2f getVelocity();

    sf::Vector2i getCoordinates(float tileSize);

    void move();
    sf::Vector2f move(std::vector<sf::FloatRect> walls, float deltaTime);
    void moveX();
    void moveY();

    void unmove();
    void unmoveX();
    void unmoveY();

    Animated_Sprite& getSprite();

    void setLevel(unsigned int nlevel);

    Projectile* attack(sf::Vector2f target);

    bool isAttacking();
    void setAttacking(bool n);

    Weapon& getEquippedWeapon();

    Entity_State getState();

    const std::vector<Ability>& getAbilities();

    void addAbility(Ability ability);

protected:
    Entity_Type type;
    Entity_State state = Entity_State::IDLE;
    Entity_State lastState = Entity_State::IDLE;

    Animated_Sprite sprite;
    sf::RectangleShape hpFrame;
    sf::RectangleShape hpBar;

    //sf::Text levelText;
    //sf::RectangleShape levelFrame;

    const static sf::Color color_hpGood;
    const static sf::Color color_hpBad;

    const static sf::Vector2f hpSize;

    std::string name;

    std::vector<Ability> abilities;

    int hpCurrent;
    int hpMax;

    unsigned int level;

    std::vector<Weapon> weapons;
    unsigned int equippedWeapon;

    void animate();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void updateHP();

    float speed_orthogonal;
    float speed_diagonal;

    void move(sf::Vector2f v);

    sf::Vector2f velocity;

    void setVelocity();

    const static sf::Vector2f spriteSize;

    const static float hpOffset;
    const static float levelOffset;

    void setSpriteDirection();

    bool attacking = false;

    void directCheck();

    bool up = false,
         down = false,
         left = false,
         right = false;

    Faction faction;

    void prepUI();

    std::map<Damage::Type, float> resistance;

    bool attackFrame = false;
};
