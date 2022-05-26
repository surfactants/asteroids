#pragma once

#include "entity.hpp"
#include "direction.hpp"

class Player : public Entity{
public:
    Player();

    Direction hMove;
    Direction vMove;

    void update() override;
protected:
private:
    sf::Texture texture;
    void checkWASD();
};
