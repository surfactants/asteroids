#include "projectile_manager.hpp"
#include <iostream>

Projectile_Manager::Projectile_Manager(){
    Projectile::loadTexture();
}

void Projectile_Manager::create(Projectile p){
    std::cout << "\nprojectile has been passed to manager...";
    projectiles.push_back(p);
    std::cout << "\n\tprojectile added!";
}

void Projectile_Manager::update(){
    for(auto& p : projectiles){
        p.update();
    }
}

void Projectile_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& p : projectiles){
        target.draw(p, states);
    }
}

//TODO
    //add 'bool shooting' to Entity for ease of mouse control
        //weapons need a cooldown
        //game update checks if entities are attacking, which checks if equippedWeapon is ready, which creates the projectile
        //mouse press in game() starts shooting
        //mouse release anywhere stops shooting
