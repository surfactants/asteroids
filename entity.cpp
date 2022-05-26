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
sf::Texture Entity::texture = sf::Texture();
sf::Vector2f Entity::spriteSize = sf::Vector2f(0.f, 0.f);

Entity::Entity(){
    animationState = IDLE;
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
    speed = 3.f;

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

    texture.loadFromFile("texture.png");
    sprite.setTexture(texture);

    spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);

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
        //die...
    }

    updateHP();
}

void Entity::heal(int val){
    hpCurrent += val;
    if(hpCurrent > hpMax) hpCurrent = hpMax;

    updateHP();
}

void Entity::setAnimationState(Animation_State newState){
    animationState = newState;

    //set sprite state...

    animationTimer.restart();
}

void Entity::startAnimation(){
    //sprite.setTextureRect()
        //x = 0, y derived from animation state, size consistent
}

void Entity::update(){
    move();
    animate();
}

void Entity::animate(){
    if(animationTimer.getElapsedTime().asMilliseconds() >= animationFrameTime){
        //animate...
            //iterate to next sprite frame, by shifting textureRect to the right
                //if that places it out of bounds, shift back to the beginning

        animationTimer.restart();
    }
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite, states);
    target.draw(hpFrame, states);
    target.draw(hpBar, states);
    target.draw(levelFrame, states);
    target.draw(levelText, states);
}

void Entity::updateHP(){
    double factor = (double)hpCurrent / hpMax;
    hpBar.setSize(sf::Vector2f(hpSize.x * factor, hpSize.y));
}

void Entity::move(){
    move(velocity);
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

sf::Sprite& Entity::getSprite(){
    return sprite;
}

void Entity::setLevel(unsigned int nlevel){
    level = nlevel;
    levelText.setString(std::to_string(level));
}

void Entity::directLeft(){
    velocity.x = -speed;
    setSpriteDirection();
}

void Entity::directRight(){
    velocity.x = speed;
    setSpriteDirection();
}

void Entity::directUp(){
    velocity.y = -speed;
    setSpriteDirection();
}

void Entity::directDown(){
    velocity.y = speed;
    setSpriteDirection();
}

void Entity::stopHorizontal(){
    velocity.x = 0.f;
    setSpriteDirection();
}

void Entity::stopVertical(){
    velocity.y = 0.f;
    setSpriteDirection();
}

void Entity::stop(){
    stopHorizontal();
    stopVertical();
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

void Entity::setSpriteDirection(){
    sf::Vector2f scale = sprite.getScale();
    if(velocity.x == 0.f){
        if(velocity.y > 0.f) scale.y = 1.f;
        else if(velocity.y < 0.f) scale.y = -1.f;
    }
    else{
        scale.y = 1.f;
        if(velocity.x > 0.f) scale.x = 1.f;
        else if(velocity.x < 0.f) scale.x = -1.f;
    }
    sprite.setScale(scale);
}
