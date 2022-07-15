#include "player.hpp"

Player::Player(){
    hMove = NULLSIDE;
    vMove = NULLSIDE;

    texture.loadFromFile("textures/entity.png");
    sprite = Animated_Sprite(texture, sf::Vector2i(64, 64));
}

void Player::update(){
    checkWASD();
    sprite.update();
}

void Player::checkWASD(){
    bool w = (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));

    bool a = (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));

    bool s = (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    bool d = (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
           || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));

    bool v = (vMove != NULLSIDE);
    bool h = (hMove != NULLSIDE);

    bool wasd = (w || a || s || d);

    if((v || h)){
        if(!wasd){
            stop();
            vMove = NULLSIDE;
            hMove = NULLSIDE;
            return;
        }
        else{
            if(v && !w && !s){
                vMove = NULLSIDE;
                stopVertical();
                setSpriteDirection();
            }
            if(h && !a && !d){
                hMove = NULLSIDE;
                stopHorizontal();
                setSpriteDirection();
            }
        }
    }

    if(v && !(w || s)){
       vMove = NULLSIDE;
       setSpriteDirection();
    }
    else if(vMove != NORTH && w){
        vMove = NORTH;
        directUp();
    }
    else if(vMove != SOUTH && s){
        vMove = SOUTH;
        directDown();
    }

    if(h && !(a || d)){
        hMove = NULLSIDE;
        setSpriteDirection();
    }
    else if(hMove != EAST && d){
        hMove = EAST;
        directRight();
    }
    else if(hMove != WEST && a){
        hMove = WEST;
        directLeft();
    }

    //IF NOT MOVING:
        //NO KEYS PRESSED:
            //RETURN
        //ANY KEY PRESSED:
            //SET ANIMATION STATE TO MOVING
            //SET HMOVE AND VMOVE BASED ON KEYS PRESSED

    //ELSE IF MOVING:
        //NO KEYS PRESSED:
            //SET ANIMATION STATE TO IDLE
        //KEYS PRESSED
            //IF(!DIRECTION && D_KEY_PRESSED):
                //DIRECT IN THAT DIRECTION

    ///////////////////////////////////
/*
    if(vMove == NULLSIDE && w){
        vMove = NORTH;
        directUp();
    }
    else if(vMove == NULLSIDE && s){
        vMove = SOUTH;
        directDown();
    }
    else if(vMove == NORTH && !w){
        vMove = NULLSIDE;
        stopVertical();
    }
    else if(vMove == SOUTH && !s){
        vMove = NULLSIDE;
        stopVertical();
    }

    if(hMove == NULLSIDE && a){
        hMove = WEST;
        directLeft();
    }
    else if(hMove == NULLSIDE && d){
        hMove = EAST;
        directRight();
    }
    else if(hMove == WEST && !a){
        hMove = NULLSIDE;
        stopHorizontal();
    }
    else if(hMove == EAST && !d){
        hMove = NULLSIDE;
        stopHorizontal();
    }*/
}
