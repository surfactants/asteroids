#pragma once

#include <abilities/projectile_manager.hpp>

#include <entity/enemy_manager.hpp>
#include <entity/player.hpp>

#include <world/world.hpp>

/////////////////////////////////////////////////////////////
/// \brief
///
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
