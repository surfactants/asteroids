#pragma once

#include <world/direction.hpp>

#include "entity.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
class Player : public Entity {
public:
    Player();
    Player(Entity_Data e, sf::Texture& texture);

    Direction hMove;
    Direction vMove;

    void upStart();
    void upEnd();

    void downStart();
    void downEnd();

    void leftStart();
    void leftEnd();

    void rightStart();
    void rightEnd();

    void update() override;

    void setPlayerAbilities();
};
