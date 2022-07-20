#include "entity.hpp"
#include "prng.hpp"
#include "primordial.hpp"
#include <iostream>

const sf::Color Entity::color_hpGood = sf::Color(10, 230, 10);
const sf::Color Entity::color_hpBad = sf::Color(230, 10, 10);
const sf::Vector2f Entity::hpSize = sf::Vector2f(80, 8);

const float Entity::hpOffset = 14.f;
const float Entity::levelOffset = 20.f;

sf::Font Entity::font = sf::Font();

const sf::Vector2f Entity::spriteSize = sf::Vector2f(64.f, 64.f);
const sf::Vector2f Entity::sheetSize = sf::Vector2f(0.f, 0.f);

Entity::Entity()
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

    armorFactor = 0.d;

    velocity = sf::Vector2f(0.f, 0.f);
    speed_orthogonal = 3.f;
    speed_diagonal = speed_orthogonal * sqrt2_inv;

    setLevel(prng::number(1u, 99u));

    font.loadFromFile("BubblerOne-Regular.ttf");

    levelText.setFont(font);
    levelText.setFillColor(sf::Color::White);
    levelText.setCharacterSize(26);

    levelFrame.setSize(sf::Vector2f(24.f, 24.f));
    levelFrame.setOrigin(levelFrame.getSize() / 2.f);
    levelFrame.setFillColor(sf::Color(125, 125, 125));
    levelFrame.setOutlineColor(sf::Color(225, 225, 225));
    levelFrame.setOutlineThickness(2);

    //spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);

    sprite.setOrigin(spriteSize / 2.f);
    sf::Vector2f hpOrigin((hpSize.x / 2.f) - levelOffset, ((hpSize.y / 2.f) + (spriteSize.y / 2.f) + hpOffset));
    hpFrame.setOrigin(hpOrigin);
    hpBar.setOrigin(hpOrigin);
    centerText(levelText);
    sf::Vector2f levelOrigin = hpOrigin + levelText.getOrigin();
    levelOrigin.x += levelOffset;
    levelText.setOrigin(levelOrigin);
    levelOrigin = hpOrigin + levelFrame.getOrigin();
    levelOrigin.x += levelOffset;
    levelFrame.setOrigin(levelOrigin);

    weapons.push_back(Weapon("test", 8));
    equippedWeapon = 0;
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
        dead = true;
        sprite.setAnimationState(DYING);
    }

    updateHP();
}

void Entity::heal(int val){
    hpCurrent += val;
    if(hpCurrent > hpMax) hpCurrent = hpMax;

    updateHP();
}

void Entity::startAnimation(){
    //sprite.setTextureRect()
        //x = 0, y derived from animation state, size consistent
}

void Entity::update(){
    move();
    sprite.update();
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
    if(!dead){
        target.draw(hpFrame, states);
        target.draw(hpBar, states);
        target.draw(levelFrame, states);
        target.draw(levelText, states);
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
        levelFrame.move(velocity.x, 0.f);
        levelText.move(velocity.x, 0.f);
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
        levelFrame.move(0.f, velocity.y);
        levelText.move(0.f, velocity.y);
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
    levelFrame.move(v);
    levelText.move(v);
}

Animated_Sprite& Entity::getSprite(){
    return sprite;
}

void Entity::setLevel(unsigned int nlevel){
    level = nlevel;
    levelText.setString(std::to_string(level));
}

void Entity::directLeft(){
    directCheck();
    velocity.x = -speed_orthogonal;
    direction = WEST;
    setSpriteDirection();
}

void Entity::directRight(){
    directCheck();
    velocity.x = speed_orthogonal;
    direction = EAST;
    setSpriteDirection();
}

void Entity::directUp(){
    directCheck();
    velocity.y = -speed_orthogonal;
    direction = NORTH;
    setSpriteDirection();
}

void Entity::directDown(){
    directCheck();
    velocity.y = speed_orthogonal;
    direction = SOUTH;
    setSpriteDirection();
}

void Entity::directCheck(){
    if(velocity.x == 0 && velocity.y == 0){
        sprite.setAnimationState(MOVING);
    }
}

void Entity::stopHorizontal(){
    velocity.x = 0.f;
    setSpriteDirection();
    if(velocity.y == 0.f) sprite.setAnimationState(IDLE);
}

void Entity::stopVertical(){
    velocity.y = 0.f;
    setSpriteDirection();
    if(velocity.x == 0.f) sprite.setAnimationState(IDLE);
}

void Entity::stop(){
    up = false;
    down = false;
    left = false;
    right = false;
    stopHorizontal();
    stopVertical();
    setVelocity();

}

void Entity::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
    hpFrame.setPosition(pos);
    hpBar.setPosition(pos);
    levelFrame.setPosition(pos);
    levelText.setPosition(pos);
}

sf::Vector2f Entity::getVelocity(){
    return velocity;
}

sf::Vector2i Entity::getCoordinates(float tileSize){
    return sf::Vector2i(getPosition() / tileSize);
}

void Entity::setDirection(Direction ndirect){
    direction = ndirect;
    setSpriteDirection();
}

void Entity::setSpriteDirection(){
    Direction d = sprite.getDirection();
    if(velocity.x == 0.f){
        if(velocity.y < 0.f) d = NORTH;
        else if(velocity.y > 0.f) d = SOUTH;
    }
    else{
        if(velocity.x > 0.f) d = EAST;
        else if(velocity.x < 0.f) d = WEST;
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

bool Entity::isDead(){
    return dead;
}

Direction Entity::getDirection(){
    return direction;
}

void Entity::setVelocity(){
    std::cout << "\n\nSETTING VELOCITY";
    if(!up && !down && !left && !right){
        std::cout << "\n\tno keys pressed, setting velocity to 0";
        velocity = sf::Vector2f(0.f, 0.f);
        return;
    }

    float speed = speed_orthogonal;
    if((up && left) || (up && right) || (down && left) || (down && right)){
        std::cout << "\n\tdiagonal detected, changing speed";
        speed = speed_diagonal;
    }

    if((!left && !right) || (left && right)){
        std::cout << "\n\tleft and right canceling each other";
        velocity.x = 0.f;
    }
    else if(left && !right){
        std::cout << "\n\tdirecting left";
        velocity.x = -speed;
    }
    else if(!left && right){
        std::cout << "\n\tdirecting right";
        velocity.x = speed;
    }

    if(!up && !down){
        std::cout << "\n\tup and down canceling each other";
        velocity.y = 0.f;
    }
    else if(up && !down){
        std::cout << "\n\tdirecting up";
        velocity.y = -speed;
    }
    else if(!up && down){
        std::cout << "\n\tdirecting down";
        velocity.y = speed;
    }
}
