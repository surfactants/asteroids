#include "collider.hpp"
#include <iostream>

Collider::Collider(){
}

void Collider::checkProjectiles(std::vector<Projectile>& projectiles,
                          std::vector<Enemy>& enemies,
                          Player& player,
                          World& world)
{
    for(unsigned int i = 0; i < projectiles.size(); ++i){
        //check wall collision

        if(projectiles[i].isPlayer()){
            for(unsigned int e = 0; e < enemies.size(); ++e){
                if(projectiles[i].getBounds().intersects(enemies[e].getSprite().getGlobalBounds())){
                    enemies[e].damage(50);
                    if(enemies[e].getHPCurrent() <= 0){
                        enemies.erase(enemies.begin() + e--);
                    }
                    projectiles.erase(projectiles.begin() + i--);
                    break;
                }
            }
        }
        else{
            if(projectiles[i].getBounds().intersects(player.getSprite().getGlobalBounds())){
                player.damage(10);
                projectiles.erase(projectiles.begin() + i--);
                continue;
            }
        }
    }
}
