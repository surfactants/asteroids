#pragma once

#include <entity/enemy.hpp>
#include <entity/entity_state.hpp>
#include <entity/player.hpp>

/////////////////////////////////////////////////////////////
/// \brief
///
class AI {
public:
    void decide(Enemy& enemy, Player& player);
};
