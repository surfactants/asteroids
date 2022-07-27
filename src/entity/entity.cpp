#include <entity/entity.hpp>
#include <util/prng.hpp>
#include <util/primordial.hpp>
#include <resources/font_manager.hpp>

const sf::Color Entity::color_hpGood = sf::Color(10, 230, 10);
const sf::Color Entity::color_hpBad = sf::Color(230, 10, 10);
const sf::Vector2f Entity::hpSize = sf::Vector2f(80, 8);

const float Entity::hpOffset = 14.f;
const float Entity::levelOffset = 20.f;

const sf::Vector2f Entity::spriteSize = sf::Vector2f(64.f, 64.f);

Entity::Entity()
{
    armorFactor = 0.d;

    velocity = sf::Vector2f(0.f, 0.f);
    speed_orthogonal = 3.f;
    speed_diagonal = speed_orthogonal * sqrt2_inv;

    weapons.push_back(Weapon("test", 8));
    equippedWeapon = 0;
    prepUI();
}

Entity::Entity(Entity_Data& e, sf::Texture* texture){
    armorFactor = 0.d;

    velocity = sf::Vector2f(0.f, 0.f);
    speed_orthogonal = 3.f;
    speed_diagonal = speed_orthogonal * sqrt2_inv;

    weapons.push_back(Weapon("test", 8));
    equippedWeapon = 0;
    prepUI();

    name = e.name;
    faction = e.faction;
    type = e.type;
    sf::Vector2i size = e.size;
    sprite = Animated_Sprite(*texture, size, e.aCount);
}

void Entity::prepUI(){
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
/*
    levelText.setFont(Font_Manager::get(FONT_UI));
    levelText.setFillColor(sf::Color::White);
    levelText.setCharacterSize(26);
    centerText(levelText);

    levelFrame.setSize(sf::Vector2f(24.f, 24.f));
    levelFrame.setOrigin(levelFrame.getSize() / 2.f);
    levelFrame.setFillColor(sf::Color(125, 125, 125));
    levelFrame.setOutlineColor(sf::Color(225, 225, 225));
    levelFrame.setOutlineThickness(2);

    sf::Vector2f levelOrigin = hpOrigin + levelText.getOrigin();
    levelOrigin.x += levelOffset;
    levelText.setOrigin(levelOrigin);
    levelOrigin = hpOrigin + levelFrame.getOrigin();
    levelOrigin.x += levelOffset;
    levelFrame.setOrigin(levelOrigin);
*/

    sf::Vector2f hpOrigin(hpSize.x / 2.f, (hpSize.y / 2.f) + (spriteSize.y / 1.5f));
    hpFrame.setOrigin(hpOrigin);
    hpBar.setOrigin(hpOrigin);
}

sf::Vector2f Entity::getPosition(){
    return sprite.getPosition();
}

int Entity::getHPCurrent(){
    return hpCurrent;
}

int Entity::getHPMax(){
    return hpMax;
}

unsigned int Entity::getLevel(){
    return level;
}

void Entity::damage(int val){
    val -= (val * armorFactor);
    hpCurrent -= val;

    if(hpCurrent <= 0){
        hpCurrent = 0;
        stop();
        setState(DYING);
    }

    updateHP();
}

void Entity::heal(int val){
    hpCurrent += val;
    if(hpCurrent > hpMax) hpCurrent = hpMax;

    updateHP();
}

void Entity::update(){
    if(state < DEAD){
        move();
        sprite.update();
        if(state == DYING){
            state = sprite.getState();
        }
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
    if(state < DYING){
        target.draw(hpFrame, states);
        target.draw(hpBar, states);
        //target.draw(levelFrame, states);
        //target.draw(levelText, states);
    }
}

void Entity::updateHP(){
    double factor = (double)hpCurrent / hpMax;
    hpBar.setSize(sf::Vector2f(hpSize.x * factor, hpSize.y));
}

void Entity::move(){
    move(velocity);
}

sf::Vector2f Entity::move(std::vector<sf::FloatRect> walls){
    sf::Vector2f offset(0.f, 0.f);
    if(offset == velocity) return offset;

    bool good = true;
    sprite.move(velocity.x, 0.f);
    for(const auto& wall : walls){
        if(wall.intersects(sprite.getGlobalBounds())){
            sprite.move(-velocity.x, 0.f);
            good = false;
        }
    }

    if(good){
        hpFrame.move(velocity.x, 0.f);
        hpBar.move(velocity.x, 0.f);
        //levelFrame.move(velocity.x, 0.f);
        //levelText.move(velocity.x, 0.f);
        offset.x = velocity.x;
    }
    else good = true;
    sprite.move(0.f, velocity.y);
    for(const auto& wall : walls){
        if(wall.intersects(sprite.getGlobalBounds())){
            sprite.move(0.f, -velocity.y);
            good = false;
        }
    }
    if(good){
        hpFrame.move(0.f, velocity.y);
        hpBar.move(0.f, velocity.y);
        //levelFrame.move(0.f, velocity.y);
        //levelText.move(0.f, velocity.y);
        offset.y = velocity.y;
    }

    return offset;
}

void Entity::moveX(){
    move(sf::Vector2f(velocity.x, 0.f));
}

void Entity::moveY(){
    move(sf::Vector2f(0.f, velocity.y));
}

void Entity::unmove(){
    move(-velocity);
}

void Entity::unmoveX(){
    move(sf::Vector2f(-velocity.x, 0.f));
}

void Entity::unmoveY(){
    move(sf::Vector2f(0.f, -velocity.y));
}

void Entity::move(sf::Vector2f v){
    sprite.move(v);
    hpFrame.move(v);
    hpBar.move(v);
    //levelFrame.move(v);
    //levelText.move(v);
}

Animated_Sprite& Entity::getSprite(){
    return sprite;
}

void Entity::setLevel(unsigned int nlevel){
    level = nlevel;
    //levelText.setString(std::to_string(level));
}

void Entity::stop(){
    up = false;
    down = false;
    left = false;
    right = false;
    setVelocity();
    setState(IDLE);

}

void Entity::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
    hpFrame.setPosition(pos);
    hpBar.setPosition(pos);
    //levelFrame.setPosition(pos);
    //levelText.setPosition(pos);
}

sf::Vector2f Entity::getVelocity(){
    return velocity;
}

sf::Vector2i Entity::getCoordinates(float tileSize){
    return sf::Vector2i(getPosition() / tileSize);
}

void Entity::setSpriteDirection(){
    Direction d = sprite.getDirection();
    if(std::abs(velocity.y) < std::abs(velocity.x)){
        if(velocity.x > 0.f) d = EAST;
        else if(velocity.x < 0.f) d = WEST;
    }
    else{
        if(velocity.y < 0.f) d = NORTH;
        else if(velocity.y > 0.f) d = SOUTH;
    }
    sprite.setDirection(d);
}

Weapon& Entity::getEquippedWeapon(){
    return weapons[equippedWeapon];
}

Projectile Entity::attack(sf::Vector2f target){
    return Projectile(getPosition(), target, weapons[equippedWeapon].getProjectile());
}

bool Entity::isAttacking(){
    return attacking;
}

void Entity::setAttacking(bool n){
    attacking = n;
}

void Entity::setVelocity(){
    if(velocity.x == 0.f && velocity.y == 0.f
    && !up && !down && !left && !right){
        velocity = sf::Vector2f(0.f, 0.f);
        return;
    }

    float speed = speed_orthogonal;
    if((up && left) || (up && right) || (down && left) || (down && right)){
        speed = speed_diagonal;
    }

    if((!left && !right) || (left && right)){
        velocity.x = 0.f;
    }
    else if(left && !right){
        velocity.x = -speed;
    }
    else if(!left && right){
        velocity.x = speed;
    }

    if(!up && !down){
        velocity.y = 0.f;
    }
    else if(up && !down){
        velocity.y = -speed;
    }
    else if(!up && down){
        velocity.y = speed;
    }

    if(sprite.getAnimationState() != IDLE
    && velocity.x == 0.f && velocity.y == 0.f){
        setState(IDLE);
    }
    else if(sprite.getAnimationState() != MOVING
    && (velocity.x != 0.f || velocity.y != 0.f)){
        setState(MOVING);
    }

    setSpriteDirection();
}

void Entity::setState(Entity_State nstate){
    if(state != nstate){
        state = nstate;
        sprite.setAnimationState(state);
    }
}

Entity_State Entity::getState(){
    return state;
}
