#pragma once

#include <SFML/Graphics.hpp>
#include "weapon.hpp"

enum Animation_State{
    IDLE,
    MOVE,
    SHOOT,
    MELEE,
    DEATH
};

/////////////////////////////////////////////////////////////
/// \brief
///
class Entity : public sf::Drawable{
public:
    Entity();

    sf::Vector2f getPosition();

    int getHPCurrent();
    int getHPMax();

    unsigned int getLevel();

    void damage(int val);
    void heal(int val);

    void setAnimationState(Animation_State newState);

    void startAnimation(); //resets textureRect xpos to 0, and ypos based on

    virtual void update();

    void directLeft();
    void directRight();
    void directUp();
    void directDown();
    void stopHorizontal();
    void stopVertical();
    void stop();

    void setPosition(sf::Vector2f pos);

    sf::Vector2f getVelocity();

    sf::Vector2i getCoordinates(float tileSize);

    void move();
    void moveX();
    void moveY();

    void unmove();
    void unmoveX();
    void unmoveY();

    sf::Sprite& getSprite();

    void setLevel(unsigned int nlevel);

    Projectile attack(sf::Vector2f target);

    bool isAttacking();
    void setAttacking(bool n);

    Weapon& getEquippedWeapon();

protected:
    sf::Sprite sprite;
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

    Animation_State animationState;
        sf::Clock animationTimer;
        const static int animationFrameTime = 500;

    void updateHP();

    float speed;

    void move(sf::Vector2f v);

    sf::Vector2f velocity;

    static sf::Font font;
    static sf::Texture texture;

    static sf::Vector2f spriteSize;

    const static float hpOffset;
    const static float levelOffset;

    void setSpriteDirection();

    bool attacking = false;
};
