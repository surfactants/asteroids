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
        sf::FloatRect bounds = projectiles[i].getBounds();

        bool deleted = false;

        std::vector<sf::FloatRect> walls = world.getLocalWalls(projectiles[i].getPosition());
        if(walls.size() > 0){
            for(const auto& wall : walls){
                if(bounds.intersects(wall)){
                    deleted = true;
                    break;
                }
            }
        }

        if(!deleted){
            if(projectiles[i].isPlayer()){
                for(auto& enemy : enemies){
                    if(!enemy.isDead() && projectiles[i].getBounds().intersects(enemy.getSprite().getGlobalBounds())){
                        enemy.damage(50);
                        deleted = true;
                        break;
                    }
                }
            }
            else{
                if(projectiles[i].getBounds().intersects(player.getSprite().getGlobalBounds())){
                    player.damage(10);
                    continue;
                }
            }
        }

        if(deleted){
            projectiles.erase(projectiles.begin() + i--);
        }

    }
}
