#pragma once
#include <entity/entity_state.hpp>
#include <entity/enemy.hpp>
#include <entity/player.hpp>

class AI{
public:
    void decide(Enemy& enemy, Player& player);
};
