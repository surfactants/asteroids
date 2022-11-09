#pragma once

#include <entity/entity.hpp>
#include <world/direction.hpp>

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

private:
    bool moveInCast(bool starting);
};
