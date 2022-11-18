#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <abilities/ability.hpp>

#include <animation/animated_sprite.hpp>

#include <ui/healthbar.hpp>

#include <world/direction.hpp>

#include "damage.hpp"
#include "entity_data.hpp"

#define ABILITY_COUNT 4

/////////////////////////////////////////////////////////////
/// \brief
///
class Entity : public sf::Drawable {
public:
    Entity() = default;
    Entity(Entity_Data& e, sf::Texture& texture);

    sf::Vector2f getPosition();

    int getHPCurrent() const;
    int getHPMax() const;

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

    const std::string& getName() const;
    const std::string& getDescription() const;

protected:
    Entity_Type type;
    Entity_State state = Entity_State::IDLE;
    Entity_State lastState = Entity_State::IDLE;

    Animated_Sprite sprite;

    int casting { -1 };

    sf::Vector2f target { 0.f, 0.f };

    std::string name;
    std::string description;

    std::vector<Ability> abilities;

    int hpCurrent;
    int hpMax;

    unsigned int level;

    void animate();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    float speed_orthogonal;
    float speed_diagonal;

    void move(sf::Vector2f v);

    sf::Vector2f velocity;

    void setVelocity();

    void setSpriteDirection();

    void directCheck();

    bool up = false,
         down = false,
         left = false,
         right = false;

    Faction faction;

    std::map<Damage::Type, float> resistance;

    bool castFrame = false;

    void calculateCastDirection();

    bool castLock { false };

    Healthbar healthbar;

    void placeHealthbar();
};
