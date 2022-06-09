#include "minimap.hpp"
#include "prng.hpp"
#include <iostream>
#include "collision.hpp"

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
    reset();
}

void Minimap::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.setView(view);

    target.draw(backdrop, states);

    for(const auto& blip : blips) target.draw(blip, states);

    target.draw(line, states);

    target.draw(frame, states);

    target.draw(center, states);
}

void Minimap::update(std::vector<sf::Vector2f> epos){
    for(unsigned int b = 0; b < blips.size(); ++b){
        blips[b].update();
        if(blips[b].dead) blips.erase(blips.begin() + b--);
    }
    for(auto& blip : blips) blip.update();
    line.rotate(.8f);

    for(auto& e : epos){
        //e /= 4.f;
        if(collide::pointRect((e), line)){
            blips.push_back(Blip(e));
        }
    }
}

void Minimap::Blip::update(){
    if(decayClock.getElapsedTime().asMilliseconds() >= 50){
        decayClock.restart();
        if(r == 0 && g == 0 && b == 0){
            dead = true;
        }
        else{
            if(r > 0) r--;
            if(g > 0) g--;
            if(b > 0) b--;
            refill();
        }
    }
}

void Minimap::Blip::reset(){
    dead = false;
    r = 250;
    g = 75;
    b = 75;
    refill();
}

void Minimap::Blip::refill(){
    setFillColor(sf::Color(r, g, b));
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

    line.setSize(sf::Vector2f(8.f, r));
    line.setOrigin(sf::Vector2f(4.f, r));
    line.setPosition(0.f, 0.f);
}
