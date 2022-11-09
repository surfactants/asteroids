#pragma once

#include <SFML/Graphics.hpp>
#include <abilities/ability.hpp>
#include <animation/animated_sprite.hpp>
#include <entity/damage.hpp>
#include <entity/entity_data.hpp>
#include <vector>
#include <world/direction.hpp>

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

    Projectile cast();

    bool isCasting();
    void setCasting();

    Entity_State getState();

    const std::vector<Ability>& getAbilities();

    void addAbility(Ability ability);

    void loadAbilities(const std::map<std::string, Ability>& abilities);

    void castAbility(const size_t a);

    void setTarget(sf::Vector2f target);

    void checkCast();

    void uncast();

    bool readyToCast();

protected:
    Entity_Type type;
    Entity_State state = Entity_State::IDLE;
    Entity_State lastState = Entity_State::IDLE;

    Animated_Sprite sprite;
    sf::RectangleShape hpFrame;
    sf::RectangleShape hpBar;

    int casting { -1 };

    //sf::Text levelText;
    //sf::RectangleShape levelFrame;

    sf::Vector2f target { 0.f, 0.f };

    const static sf::Color color_hpGood;
    const static sf::Color color_hpBad;

    const static sf::Vector2f hpSize;

    std::string name;

    std::vector<Ability> abilities;

    int hpCurrent;
    int hpMax;

    unsigned int level;

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

    void directCheck();

    bool up = false,
         down = false,
         left = false,
         right = false;

    Faction faction;

    void prepUI();

    std::map<Damage::Type, float> resistance;

    bool castFrame = false;

    void calculateCastDirection();

    bool castLock { false };
};
