#pragma once

#include <SFML/Graphics.hpp>
#include "direction.hpp"

enum Animation_State{
    MOVING,
    DYING,
    IDLE
};

class Animated_Sprite : public sf::Sprite{
public:
    Animated_Sprite(){}
    Animated_Sprite(sf::Texture& ntexture, sf::Vector2i nsize);

    void setAnimationState(Animation_State nstate);

    void setDirection(Direction ndirection);
    Direction getDirection();

    void update();

private:
    sf::Vector2i size;   /**< frame size for setTextureRect()   */

    int animationY{};    /**< offset of specific animation from the start of the spritesheet    */
    int directionY{};    /**< offset of specific direction from animationY                      */

    Animation_State state{};
    Direction direction{};

    sf::Clock frameTimer;
    const static int frameThreshold{250};

    int frame{};
    const static int frameLimit = 3;

    void updateFrame();
};