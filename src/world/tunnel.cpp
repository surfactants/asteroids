#include <world/tunnel.hpp>
#include <util/prng.hpp>

/////////////////////////////////////////////////////////////
Tunnel::Tunnel(sf::Vector2i& pos, Direction ndirect){
    nodes.push_back(Node(pos));
    direction = ndirect;

    Direction sideways = NULLSIDE;

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
                    sideways = WEST;
                    break;
                case 0:
                    sideways = NULLSIDE;
                    break;
                case 1:
                    sideways = EAST;
                    break;
                default:
                    break;
                }
            }
        }

        if(!forward && sideways == NULLSIDE){
            Direction t;
            if(prng::boolean()) t = WEST;
            else t = EAST;
            moveDirection(pos, normalizeDirection(direction, t), distance);
        }

        if(sideways != NULLSIDE){
            moveDirection(pos, normalizeDirection(direction, sideways), distance);
        }

        nodes.push_back(Node(pos));
    }
}
