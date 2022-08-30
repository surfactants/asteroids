#include <entity/projectile_manager.hpp>

Projectile_Manager::Projectile_Manager(){}

void Projectile_Manager::create(Projectile p){
    projectiles.push_back(p);
}

void Projectile_Manager::update(float deltaTime){
    for(auto& p : projectiles){
        p.update(deltaTime);
    }
}

void Projectile_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& p : projectiles){
        target.draw(p, states);
    }
}

std::vector<Projectile>& Projectile_Manager::getProjectiles(){
    return projectiles;
}
