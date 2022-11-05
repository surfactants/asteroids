#pragma once

#include <entity/enemy_manager.hpp>
#include <entity/player.hpp>
#include <entity/projectile_manager.hpp>
#include <world/world.hpp>

class Collider {
public:
    Collider();

    void checkProjectiles(std::vector<Projectile>& projectiles,
        std::vector<Enemy>& enemies,
        Player& player,
        World& world);

protected:
private:
};
