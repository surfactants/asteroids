#include "minimap.hpp"
#include "prng.hpp"
#include <iostream>
#include "collision.hpp"
#include "sfml-vector2-extension.hpp"

const float Minimap::Blip::timeThreshold = 0.5f;

Minimap::Minimap(){
    backdrop.setPosition(sf::Vector2f(0.f, 0.f));
    backdrop.setSize(sf::Vector2f(1600.f, 1600.f));
    backdrop.setFillColor(sf::Color(15, 15, 15));
    backdrop.setOrigin(backdrop.getSize() / 2.f);

    frame.setOutlineColor(sf::Color(200, 200, 200));
    frame.setOutlineThickness(124.f);
    frame.setPointCount(64);
    frame.setFillColor(sf::Color::Transparent);

    line.setFillColor(sf::Color(190, 80, 110));

    float r = 4.f;
    center.setRadius(r);
    center.setOrigin(r, r);
    center.setFillColor(sf::Color(200, 200, 200));
}

Minimap::Blip::Blip(){
    setRadius(8.f);
    setPointCount(18);
    reset();
}

Minimap::Blip::Blip(sf::Vector2f pos){
    setRadius(8.f);
    setPosition(pos);
    setPointCount(18);
    setFillColor(sf::Color::Transparent);
}

void Minimap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.setView(view);

    target.draw(backdrop, states);

    for(const auto& blip : dyingBlips) target.draw(blip, states);
    for(const auto& blip : blips) target.draw(blip.second, states);

    target.draw(line, states);

    target.draw(frame, states);

    target.draw(center, states);
}

void Minimap::initialize(std::vector<Enemy>& enemies, sf::Vector2f playerPos){
    blips.clear();
    for(unsigned int e = 0; e < enemies.size(); ++e){
        blips[e] = Blip(enemies[e].getPosition());
    }
}

void Minimap::update(std::vector<Enemy>& enemies, sf::Vector2f playerPos){
    for(auto& blip : blips){
        if(!blip.second.dead) blip.second.update();
    }

    line.rotate(.8f);

    for(unsigned int e = 0; e < enemies.size(); ++e){

        sf::Vector2f p = (playerPos - enemies[e].getPosition());
        if(!enemies[e].isDead() && collide::pointRect(p, line)){
            if(blips[e].ready()){
                if(!blips[e].dead){
                    dyingBlips.push_back(blips[e]);
                }
                blips[e].setPosition(p);
                blips[e].reset();
                std::cout << "\nenemy found at pos " << enemies[e].getPosition();
                std::cout << "\n\tchecking against player position " << playerPos;
                std::cout << "\n\tp = " << p;
                std::cout << "\n\tblip placed at " << blips[e].getPosition();
            }
        }
    }

    for(unsigned int b = 0; b < dyingBlips.size(); ++b){
        dyingBlips[b].update();
        if(dyingBlips[b].dead){
            dyingBlips.erase(dyingBlips.begin() + b--);
        }
    }
}

void Minimap::Blip::update(){
    if(decayClock.getElapsedTime().asMilliseconds() >= 50){
        decayClock.restart();
        if(a == 0){
            dead = true;
        }
        else{
            a -= 3;
            refill();
        }
    }
}

void Minimap::Blip::reset(){
    dead = false;
    a = 255;
    refill();
    timer.restart();
}

bool Minimap::Blip::ready(){
    bool r = (timer.getElapsedTime().asSeconds() >= timeThreshold);
    if(r){
        timer.restart();
    }
    return r;
}

void Minimap::Blip::refill(){
    setFillColor(sf::Color(r, g, b, a));
}

void Minimap::set(sf::Vector2f size){
    sf::Vector2f factor;
    factor.x = 0.15f;
    factor.y = (size.x * factor.x) / size.y;
    view.setSize(size.x * factor.x, size.y * factor.y);
    view.setCenter(0.f, 0.f);
    view.setViewport(sf::FloatRect(1.f - factor.x, 0.f, factor.x, factor.y));

    float r = ((factor.x * size.x) / 2.f) - 2.f;
    frame.setRadius(r);
    frame.setOrigin(r, r);

    const float lineLength = r * 4.f;

    line.setSize(sf::Vector2f(8.f, lineLength));
    line.setOrigin(sf::Vector2f(4.f, lineLength));
    line.setPosition(0.f, 0.f);
}
