#include <world/tunnel.hpp>
#include <util/prng.hpp>

/////////////////////////////////////////////////////////////
Tunnel::Tunnel(sf::Vector2i& pos, Direction ndirect){
    nodes.push_back(Node(pos));
    direction = ndirect;

    Direction sideways = Direction::NULLDIRECTION;

    unsigned int steps = prng::number(48u, 96u);

    int distance = 1;

    for(unsigned int i = 0; i < steps; ++i){

        bool forward = false;

        if(prng::boolean(.75d)){
            moveDirection(pos, direction, distance);
            forward = true;
        }

        if(prng::boolean(.10f)){
            Direction nd = sideways;
            while(nd == sideways){
                switch(prng::number(-1, 1)){
                case -1:
                    sideways = Direction::W;
                    break;
                case 0:
                    sideways = Direction::NULLDIRECTION;
                    break;
                case 1:
                    sideways = Direction::E;
                    break;
                default:
                    break;
                }
            }
        }

        if(!forward && sideways == Direction::NULLDIRECTION){
            Direction t;
            if(prng::boolean()) t = Direction::W;
            else t = Direction::E;
            moveDirection(pos, normalizeDirection(direction, t), distance);
        }

        if(sideways != Direction::NULLDIRECTION){
            moveDirection(pos, normalizeDirection(direction, sideways), distance);
        }

        nodes.push_back(Node(pos));
    }
}
