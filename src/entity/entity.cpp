#include <entity/entity.hpp>

#include <audio/sound_bus.hpp>

#include <util/primordial.hpp>
#include <util/prng.hpp>

#define SQRT2_INV 0.707106781

//////////////////////////////////////////////////////////////

Entity::Entity(Entity_Data& data, sf::Texture& texture)
{
    name = data.name;
    description = data.description;

    velocity = sf::Vector2f(0.f, 0.f);
    speed_orthogonal = data.speed;
    speed_diagonal = speed_orthogonal * SQRT2_INV;

    name = data.name;
    faction = data.faction;
    type = data.type;
    sf::Vector2i size = data.size;
    sprite = Animated_Sprite(texture, size, data.aCount, data.aThreshold);

    if(type == Entity_Type::BOSS) {
        healthbar.setHidden(true);
    }

    resistance = data.resistance;

    hpMax = 100;
    hpCurrent = hpMax;

    healthbar.setSize(sf::Vector2f(50.f, 6.f));
    healthbar.center();

    healthbar.update(hpCurrent, hpMax);

    setLevel(prng::number(1u, 99u));
}

sf::Vector2f Entity::getPosition()
{
    return sprite.getPosition();
}

int Entity::getHPCurrent() const
{
    return hpCurrent;
}

int Entity::getHPMax() const
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

    healthbar.update(hpCurrent, hpMax);
}

void Entity::heal(int val)
{
    hpCurrent += val;
    if (hpCurrent > hpMax) {
        hpCurrent = hpMax;
    }

    healthbar.update(hpCurrent, hpMax);
}

void Entity::update()
{
    if (state < Entity_State::DEAD) {
        if (state == Entity_State::DYING) {
            setState(sprite.getState());
        }
        else if (state == Entity_State::CASTING) {
            if (castLock && sprite.done()) {
                setState(lastState);
                setSpriteDirection();
                castLock = false;
            }
            else
                checkCast();
        }
        else if (isCasting() && !abilities[casting].isCooling()) {
            sprite.resetCast();
            setState(Entity_State::CASTING);
            calculateCastDirection();
        }
        sprite.update();

        for (auto& a : abilities) {
            a.checkCooldown();
        }
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    if (state < Entity_State::DEAD) {
        target.draw(healthbar, states);
    }
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
    if (offset == velocity) {
        return offset;
    }

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
            offset.x = v.x;
        }
        else {
            good = true; //prep good for y movement
        }

        sprite.move(0.f, v.y);
        for (const auto& wall : walls) {
            if (wall.intersects(sprite.getGlobalBounds())) {
                sprite.move(0.f, -v.y);
                good = false;
            }
        }
        if (good) {
            offset.y = v.y;
        }
    }

    if(offset.x != 0.f || offset.y != 0.f) {
        placeHealthbar();
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
    placeHealthbar();
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
    placeHealthbar();
}

sf::Vector2f Entity::getVelocity()
{
    return velocity;
}

sf::Vector2i Entity::getCoordinates(float tileSize)
{
    return sf::Vector2i(getPosition() / tileSize);
}

void Entity::calculateCastDirection()
{
    Direction d { Direction::NULL_DIRECTION };

    double t = calculateOrientation(getPosition(), target);

    if (t <= 22.5d || t > 337.5d) {
        d = Direction::N;
    }
    else if (t > 22.5d && t <= 67.5d) {
        d = Direction::NE;
    }
    else if (t > 67.5d && t <= 112.5d) {
        d = Direction::E;
    }
    else if (t > 112.5d && t <= 157.5d) {
        d = Direction::SE;
    }
    else if (t > 157.5d && t <= 202.5d) {
        d = Direction::S;
    }
    else if (t > 202.5d && t <= 247.5d) {
        d = Direction::SW;
    }
    else if (t > 247.5d && t <= 292.5d) {
        d = Direction::W;
    }
    else if (t > 292.5d && t <= 337.5d) {
        d = Direction::NW;
    }

    sprite.setDirection(d);
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
        if (e) {
            d = Direction::NE;
        }
        else if (w) {
            d = Direction::NW;
        }
        else {
            d = Direction::N;
        }
    }
    else if (s) {
        if (e) {
            d = Direction::SE;
        }
        else if (w) {
            d = Direction::SW;
        }
        else {
            d = Direction::S;
        }
    }
    else {
        if (e) {
            d = Direction::E;
        }
        else if (w) {
            d = Direction::W;
        }
    }

    sprite.setDirection(d);
}

Projectile Entity::cast()
{
    castFrame = false;
    Projectile p = abilities[casting].projectile;
    p.setVelocity(getPosition(), target);
    abilities[casting].startCooldown();
    Sound_Bus::addSound(abilities[casting].sound);

    return p;
}

bool Entity::isCasting()
{
    return (casting > -1);
}

void Entity::setVelocity()
{
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

    if (velocity.x == 0.f && velocity.y == 0.f
        && !up && !down && !left && !right) {
        velocity = sf::Vector2f(0.f, 0.f);
        if (state == Entity_State::CASTING) {
            lastState = Entity_State::IDLE;
        }
        else {
            setState(Entity_State::IDLE);
        }
    }
    else if (sprite.getAnimationState() != Entity_State::MOVING
        && (velocity.x != 0.f || velocity.y != 0.f)) {
        if (sprite.getAnimationState() != Entity_State::CASTING) {
            setState(Entity_State::MOVING);
            setSpriteDirection();
        }
        else {
            lastState = Entity_State::MOVING;
        }
    }
    else {
        setSpriteDirection();
    }
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
    if (state == Entity_State::CASTING) {
        calculateCastDirection();
    }
}

void Entity::castAbility(const size_t a)
{
    if (!isCasting()) {
        casting = a;
    }
}

void Entity::uncast()
{
    if (isCasting()) {
        if (state == Entity_State::CASTING) {
            sprite.resetCast();
            setState(lastState);
            if (state == Entity_State::MOVING) {
                setSpriteDirection();
            }
        }
        casting = -1;
    }
}

void Entity::checkCast()
{
    if (!castLock && sprite.lastFrame()) {
        castFrame = true;
        castLock = true;
    }
}

bool Entity::readyToCast()
{
    return castFrame;
}

const std::string& Entity::getName() const
{
    return name;
}

const std::string& Entity::getDescription() const
{
    return description;
}

void Entity::placeHealthbar()
{
    sf::Vector2f pos = getPosition();
    pos.y -= sprite.getSize().y * .6;
    healthbar.setPosition(pos);
}
