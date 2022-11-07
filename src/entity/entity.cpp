#include <entity/entity.hpp>
#include <util/primordial.hpp>
#include <util/prng.hpp>
#include <iostream>

#define SQRT2_INV 0.707106781

const sf::Color Entity::color_hpGood = sf::Color(10, 230, 10);
const sf::Color Entity::color_hpBad = sf::Color(230, 10, 10);
const sf::Vector2f Entity::hpSize = sf::Vector2f(80, 8);

const float Entity::hpOffset = 14.f;
const float Entity::levelOffset = 20.f;

const sf::Vector2f Entity::spriteSize = sf::Vector2f(64.f, 64.f);

Entity::Entity(Entity_Data& data, sf::Texture& texture)
{
    name = data.name;

    velocity = sf::Vector2f(0.f, 0.f);
    speed_orthogonal = data.speed;
    speed_diagonal = speed_orthogonal * SQRT2_INV;
    prepUI();

    name = data.name;
    faction = data.faction;
    type = data.type;
    sf::Vector2i size = data.size;
    sprite = Animated_Sprite(texture, size, data.aCount, data.aThreshold);

    resistance = data.resistance;
}

void Entity::prepUI()
{
    hpMax = 100;
    hpCurrent = hpMax;

    hpFrame.setSize(hpSize);
    hpFrame.setFillColor(color_hpBad);

    hpFrame.setOutlineColor(sf::Color(225, 225, 225));
    hpFrame.setOutlineThickness(1);

    hpFrame.setPosition(64, 64);

    hpBar.setSize(hpSize);
    hpBar.setFillColor(color_hpGood);
    hpBar.setPosition(64, 64);

    setLevel(prng::number(1u, 99u));

    sf::Vector2f hpOrigin(hpSize.x / 2.f, (hpSize.y / 2.f) + (spriteSize.y / 1.5f));
    hpFrame.setOrigin(hpOrigin);
    hpBar.setOrigin(hpOrigin);
}

sf::Vector2f Entity::getPosition()
{
    return sprite.getPosition();
}

int Entity::getHPCurrent()
{
    return hpCurrent;
}

int Entity::getHPMax()
{
    return hpMax;
}

unsigned int Entity::getLevel()
{
    return level;
}

void Entity::takeDamage(Damage dmg)
{
    hpCurrent -= dmg.val - (dmg.val * resistance[dmg.type]);

    if (hpCurrent <= 0) {
        hpCurrent = 0;
        stop();
        setState(Entity_State::DYING);
    }

    updateHP();
}

void Entity::heal(int val)
{
    hpCurrent += val;
    if (hpCurrent > hpMax)
        hpCurrent = hpMax;

    updateHP();
}

void Entity::update()
{
    if (state < Entity_State::DEAD) {
        if (state == Entity_State::DYING) {
            setState(sprite.getState());
        }
        else if (state == Entity_State::CASTING) {
            checkCast();
        }
        else if (isCasting() && !abilities[casting].isCooling()) {
            std::cout << "\t\tsetting state to casting\n";
            sprite.resetAttack();
            setState(Entity_State::CASTING);
        }
        sprite.update();
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    if (state < Entity_State::DYING) {
        target.draw(hpFrame, states);
        target.draw(hpBar, states);
    }
}

void Entity::updateHP()
{
    double factor = (double)hpCurrent / hpMax;
    hpBar.setSize(sf::Vector2f(hpSize.x * factor, hpSize.y));
}

void Entity::move()
{
    if (state == Entity_State::MOVING) {
        move(velocity);
    }
}

sf::Vector2f Entity::move(std::vector<sf::FloatRect> walls, float deltaTime)
{
    sf::Vector2f offset(0.f, 0.f);
    if (offset == velocity)
        return offset;

    sf::Vector2f v = velocity * deltaTime;

    if (state == Entity_State::MOVING) {
        bool good = true;
        sprite.move(v.x, 0.f);
        for (const auto& wall : walls) {
            if (wall.intersects(sprite.getGlobalBounds())) {
                sprite.move(-v.x, 0.f);
                good = false;
            }
        }

        if (good) {
            hpFrame.move(v.x, 0.f);
            hpBar.move(v.x, 0.f);
            offset.x = v.x;
        }
        else
            good = true;
        sprite.move(0.f, v.y);
        for (const auto& wall : walls) {
            if (wall.intersects(sprite.getGlobalBounds())) {
                sprite.move(0.f, -v.y);
                good = false;
            }
        }
        if (good) {
            hpFrame.move(0.f, v.y);
            hpBar.move(0.f, v.y);
            offset.y = v.y;
        }
    }

    return offset;
}

void Entity::moveX()
{
    move(sf::Vector2f(velocity.x, 0.f));
}

void Entity::moveY()
{
    move(sf::Vector2f(0.f, velocity.y));
}

void Entity::unmove()
{
    move(-velocity);
}

void Entity::unmoveX()
{
    move(sf::Vector2f(-velocity.x, 0.f));
}

void Entity::unmoveY()
{
    move(sf::Vector2f(0.f, -velocity.y));
}

void Entity::move(sf::Vector2f v)
{
    sprite.move(v);
    hpFrame.move(v);
    hpBar.move(v);
}

Animated_Sprite& Entity::getSprite()
{
    return sprite;
}

void Entity::setLevel(unsigned int nlevel)
{
    level = nlevel;
}

void Entity::stop()
{
    up = false;
    down = false;
    left = false;
    right = false;
    setVelocity();
    setState(Entity_State::IDLE);
}

void Entity::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
    hpFrame.setPosition(pos);
    hpBar.setPosition(pos);
}

sf::Vector2f Entity::getVelocity()
{
    return velocity;
}

sf::Vector2i Entity::getCoordinates(float tileSize)
{
    return sf::Vector2i(getPosition() / tileSize);
}

void Entity::setSpriteDirection()
{
    Direction d = sprite.getDirection();
    float threshold = speed_orthogonal * 0.15f;

    bool n = (velocity.y < -threshold),
         e = (velocity.x > threshold),
         s = (velocity.y > threshold),
         w = (velocity.x < -threshold);

    if (n) {
        if (e)
            d = Direction::NE;
        else if (w)
            d = Direction::NW;
        else
            d = Direction::N;
    }
    else if (s) {
        if (e)
            d = Direction::SE;
        else if (w)
            d = Direction::SW;
        else
            d = Direction::S;
    }
    else {
        if (e)
            d = Direction::E;
        else if (w)
            d = Direction::W;
    }

    sprite.setDirection(d);
}

Projectile Entity::cast()
{
    castFrame = false;
    Projectile p = abilities[casting].projectile;
    p.setVelocity(getPosition(), target);
    setState(lastState);

    return p;
}

bool Entity::isCasting()
{
    return (casting > -1);
}

void Entity::setVelocity()
{
    if (velocity.x == 0.f && velocity.y == 0.f
        && !up && !down && !left && !right) {
        velocity = sf::Vector2f(0.f, 0.f);
        return;
    }

    float speed = speed_orthogonal;
    if ((up && left) || (up && right) || (down && left) || (down && right)) {
        speed = speed_diagonal;
    }

    if ((!left && !right) || (left && right)) {
        velocity.x = 0.f;
    }
    else if (left && !right) {
        velocity.x = -speed;
    }
    else if (!left && right) {
        velocity.x = speed;
    }

    if (!up && !down) {
        velocity.y = 0.f;
    }
    else if (up && !down) {
        velocity.y = -speed;
    }
    else if (!up && down) {
        velocity.y = speed;
    }

    if (sprite.getAnimationState() != Entity_State::IDLE
        && velocity.x == 0.f && velocity.y == 0.f) {
        setState(Entity_State::IDLE);
    }
    else if (sprite.getAnimationState() != Entity_State::MOVING
        && sprite.getAnimationState() != Entity_State::CASTING
        && (velocity.x != 0.f || velocity.y != 0.f)) {
        setState(Entity_State::MOVING);
    }

    setSpriteDirection();
}

void Entity::setState(Entity_State nstate)
{
    if (state != nstate) {
        lastState = state;
        state = nstate;
        sprite.setAnimationState(state);
    }
}

Entity_State Entity::getState()
{
    return state;
}

const std::vector<Ability>& Entity::getAbilities()
{
    return abilities;
}

void Entity::addAbility(Ability ability)
{
    abilities.push_back(ability);
}

void Entity::loadAbilities(const std::map<std::string, Ability>& abilities)
{
}

void Entity::setTarget(sf::Vector2f target)
{
    this->target = target;
}

void Entity::castAbility(const size_t a)
{
    if (!isCasting()) {
        casting = a;
        std::cout << "\ncasting ability: " << abilityTypeToString(abilities[a].type) << "\n";
    }
}

void Entity::uncast()
{
    if(isCasting()){
        std::cout << "uncasting...\n";
        if(state == Entity_State::CASTING){
            setState(lastState);
        }
        casting = -1;
    }
}

void Entity::checkCast()
{
    if (sprite.done()) {
        castFrame = true;
        setState(lastState);
        abilities[casting].startCooldown();
        std::cout << "\tanimation finished, setting cast frame\n";
    }
}

bool Entity::readyToCast()
{
    return castFrame;
}
