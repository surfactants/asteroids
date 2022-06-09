#pragma once
#include "enemy_manager.hpp"
#include "projectile_manager.hpp"
#include "player.hpp"
#include "world.hpp"

class Collider{
public:
    Collider();

    void checkProjectiles(std::vector<Projectile>& projectiles,
                          std::vector<Enemy>& enemies,
                          Player& player,
                          World& world);

protected:
private:
};
