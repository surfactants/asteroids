#pragma once

#include <SFML/Graphics.hpp>
#include <entity/weapon.hpp>
#include <world/direction.hpp>
#include <animation/animated_sprite.hpp>
#include <vector>
#include <entity/entity_data.hpp>

#define sqrt2_inv 0.7071

/////////////////////////////////////////////////////////////
/// \brief
///
class Entity : public sf::Drawable{
public:
    Entity();
    Entity(Entity_Data& e, sf::Texture* texture);
    //Entity(const Entity& e);

    sf::Vector2f getPosition();

    int getHPCurrent();
    int getHPMax();

    unsigned int getLevel();

    void damage(int val);
    void heal(int val);

    void setState(Entity_State nstate);

    virtual void update();

    void stop();

    void setPosition(sf::Vector2f pos);

    sf::Vector2f getVelocity();

    sf::Vector2i getCoordinates(float tileSize);

    void move();
    sf::Vector2f move(std::vector<sf::FloatRect> walls);
    void moveX();
    void moveY();

    void unmove();
    void unmoveX();
    void unmoveY();

    Animated_Sprite& getSprite();

    void setLevel(unsigned int nlevel);

    Projectile attack(sf::Vector2f target);

    bool isAttacking();
    void setAttacking(bool n);

    Weapon& getEquippedWeapon();

    Entity_State getState();

protected:
    Entity_Type type;
    Entity_State state;

    Animated_Sprite sprite;
    sf::RectangleShape hpFrame;
    sf::RectangleShape hpBar;
    sf::Text levelText;
    sf::RectangleShape levelFrame;

    const static sf::Color color_hpGood;
    const static sf::Color color_hpBad;

    const static sf::Vector2f hpSize;

    std::string name;

    int hpCurrent;
    int hpMax;

    ///percentage of damage blocked by armor, 0-1.d scale
    double armorFactor;

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
         left= false,
         right = false;

    Faction faction;

    void prepUI();
};
