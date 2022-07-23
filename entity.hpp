#pragma once

#include <SFML/Graphics.hpp>
#include "weapon.hpp"
#include "direction.hpp"
#include "animated_sprite.hpp"
#include <vector>

#define sqrt2_inv 0.7071

enum Faction{
    BUGS,
    PIRATES,
    GHOSTS,
    LITHOBIOMORPHS,
    ROBOTS,
    PLAYER_FACTION,
    NULL_FACTION
};

inline std::string factionToString(Faction f){
    switch(f){
    case PLAYER_FACTION:
        return "PLAYER_FACTION";
    case BUGS:
        return "BUGS";
    case PIRATES:
        return "PIRATES";
    case GHOSTS:
        return "GHOSTS";
    case LITHOBIOMORPHS:
        return "LITHOBIOMORPHS";
    case ROBOTS:
        return "ROBOTS";
    default:
        return std::string();
    }
}

inline Faction stringToFaction(std::string s){
    if(s == "PLAYER_FACTION") return PLAYER_FACTION;
    else if(s == "BUGS") return BUGS;
    else if(s == "PIRATES") return PIRATES;
    else if(s == "GHOSTS") return GHOSTS;
    else if(s == "LITHOBIOMORPHS") return LITHOBIOMORPHS;
    else if(s == "ROBOTS") return ROBOTS;
    else return NULL_FACTION;
}

enum Entity_Type{
    MELEE_LIGHT,
    MELEE_HEAVY,
    RANGED,
    TURRET,
    BOSS,
    PLAYER,
    NULLENEMY
};

inline std::string entityTypeToString(Entity_Type e){
    switch(e){
    case MELEE_LIGHT:
        return "MELEE_LIGHT";
    case MELEE_HEAVY:
        return "MELEE_HEAVY";
    case RANGED:
        return "RANGED";
    case TURRET:
        return "TURRET";
    case BOSS:
        return "BOSS";
    default:
        return std::string();
    }

    return std::string();
}

inline Entity_Type stringToEntityType(std::string s){
    if(s == "MELEE_LIGHT") return MELEE_LIGHT;
    else if(s == "MELEE_HEAVY") return MELEE_HEAVY;
    else if(s == "RANGED") return RANGED;
    else if(s == "TURRET") return TURRET;
    else if(s == "BOSS") return BOSS;
    else return NULLENEMY;
}

struct Entity_Data{
    std::string name{};
    Faction faction;
    Entity_Type type;
    sf::Vector2i size;
    std::map<Animation_State, unsigned int> aCount;
};

/////////////////////////////////////////////////////////////
/// \brief
///
class Entity : public sf::Drawable{
public:
    Entity();
    Entity(Entity_Data& e, sf::Texture& texture);

    sf::Vector2f getPosition();

    int getHPCurrent();
    int getHPMax();

    unsigned int getLevel();

    void damage(int val);
    void heal(int val);

    void setAnimationState(Animation_State newState);

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

    bool isDead();

protected:
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

    static sf::Font font;

    const static sf::Vector2f spriteSize;

    const static float hpOffset;
    const static float levelOffset;

    void setSpriteDirection();

    bool attacking = false;

    bool dead = false;

    const static sf::Vector2f sheetSize;

    float animationBase;

    void directCheck();

    bool up = false,
         down = false,
         left= false,
         right = false;

    Faction faction;

    void prepUI();

    Entity_Type type;
};
