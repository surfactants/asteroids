////////////////////////////////////////////////////////////
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "level.hpp"
#include <iostream>
#include "primordial.hpp"
#include <unordered_map>
#include "perlin.hpp"

Room_Component::Room_Component(sf::Texture& texture){
    sprite.setTexture(texture);
}

void Room_Component::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(sprite.getGlobalBounds().intersects(getViewBounds(target.getView()))) target.draw(sprite, states);
}

Tile::Tile(sf::Texture& texture) : Room_Component(texture){
    left = nullptr;
    right = nullptr;
    up = nullptr;
    down = nullptr;
}

void Tile::setPosition(sf::Vector2f pos){
    sprite.setPosition(pos);
}

void Tile::setIndicators(){
    if(left == nullptr){
        circles.push_back(sf::CircleShape(6, 8));
        circles.back().setOrigin(circles.back().getRadius(), circles.back().getRadius());
        circles.back().setFillColor(sf::Color::Red);
        sf::Vector2f pos;
            pos.x = sprite.getGlobalBounds().left;
            pos.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f;
        circles.back().setPosition(pos);
    }

    if(right == nullptr){
        circles.push_back(sf::CircleShape(6, 8));
        circles.back().setOrigin(circles.back().getRadius(), circles.back().getRadius());
        circles.back().setFillColor(sf::Color::Red);
        sf::Vector2f pos;
            pos.x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().height;
            pos.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height / 2.f;
        circles.back().setPosition(pos);
    }

    if(up == nullptr){
        circles.push_back(sf::CircleShape(6, 8));
        circles.back().setOrigin(circles.back().getRadius(), circles.back().getRadius());
        circles.back().setFillColor(sf::Color::Red);
        sf::Vector2f pos;
            pos.x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f;
            pos.y = sprite.getGlobalBounds().top;
        circles.back().setPosition(pos);
    }

    if(down == nullptr){
        circles.push_back(sf::CircleShape(6, 8));
        circles.back().setOrigin(circles.back().getRadius(), circles.back().getRadius());
        circles.back().setFillColor(sf::Color::Red);
        sf::Vector2f pos;
            pos.x = sprite.getGlobalBounds().left + sprite.getGlobalBounds().width / 2.f;
            pos.y = sprite.getGlobalBounds().top + sprite.getGlobalBounds().height;
        circles.back().setPosition(pos);
    }
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    Room_Component::draw(target, states);
    for(const auto& it : circles) target.draw(it, states);
}

Room::Room(sf::Texture& texture){
    sf::Vector2f size(64.f, 64.f);
    sf::Vector2f pos(0.f, 0.f);

    unsigned int lSize = 64;

    for(unsigned int x = 0; x < lSize; x++){
        tiles.push_back(std::vector<Tile>());
        for(unsigned int y = 0; y < lSize; y++){
            tiles.back().push_back(Tile(texture));
            tiles.back().back().setPosition(pos);
            pos.y += size.y;
        }
        pos += sf::Vector2f(size.x, -pos.y);
    }

    Tile* tile;

    for(unsigned int x = 0; x < tiles.size(); ++x){
        for(unsigned int y = 0; y < tiles[x].size(); ++y){
            tile = &tiles[x][y];

            if(x > 0){
                tile->left = &tiles[x - 1][y];
            }
            if(x < tiles.size() - 1){
                tile->right = &tiles[x + 1][y];
            }

            if(y > 0){
                tile->up = &tiles[x][y - 1];
            }
            if(y < tiles[x].size() - 1){
                tile->down = &tiles[x][y + 1];
            }

            tile->setIndicators();
        }
    }
}

void Room::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& ix : tiles){
        for(const auto& iy : ix) target.draw(iy, states);
    }
    for(const auto& it : walls) target.draw(it, states);
    for(const auto& it : doors) target.draw(it, states);
}

Level::Level(){
    texture.loadFromFile("level.png");

    rooms.push_back(Room(texture));

    setGrid();

    generate();
}

void Level::setGrid(){
    sf::Vector2f size(64.f, 64.f);
    sf::Vector2f pos(0.f, 0.f);

    for(unsigned int x = 0; x < wsize; x++){
        grid.push_back(std::vector<sf::RectangleShape>());
        for(unsigned int y = 0; y < wsize; y++){
            grid.back().push_back(sf::RectangleShape(size));
            grid.back().back().setPosition(pos);
            grid.back().back().setFillColor(sf::Color::Transparent);
            grid.back().back().setOutlineColor(sf::Color(25, 25, 25));
            grid.back().back().setOutlineThickness(1.f);
            pos.y += size.y;
        }
        pos += sf::Vector2f(size.x, -pos.y);
    }
}

void Level::generate(){
    floor.clear();
    walls.clear();

    sf::Vector2i pos(1, 1);

    unsigned int rsize = 48;

    PerlinNoise perlin;

    double avg;

    //noise test
    for(unsigned int x = 0; x < wsize; ++x){
        for(unsigned int y = 0; y < wsize; ++y){
            double noise = perlin.noise((double)x + 0.1d, (double)y + 0.1d, 1.d);
            avg += noise;
            if(noise >= .5d){
                floor[sf::Vector2i(x, y)] = true;
                grid[x][y].setFillColor(sf::Color(50, 150, 50));
            }
            else floor[sf::Vector2i(x, y)] = false;
        }
    }

    avg/= (wsize * wsize);

    //generate floor
    for(unsigned int x = 1; x <= 48; ++x){
        for(unsigned int y = 1; y <= 48; ++y){
            if(prng::boolean(.6d)){
                //floor[sf::Vector2i(x, y)] = true;
            }
            else floor[sf::Vector2i(x, y)] = false;
        }
    }

    gen = 1;
}

void Level::gen2(){
    //check that each floor tile has at least one orthogonally contiguous partner
    for(unsigned int x = 0; x < wsize; ++x){
        for(unsigned int y = 0; y < wsize; ++y){
            sf::Vector2i check(x, y);
            if(floor[check]){
                bool changing = true;
                if(floor[check + sf::Vector2i(-1, 0)]
                || floor[check + sf::Vector2i(1, 0)]
                || floor[check + sf::Vector2i(0, -1)]
                || floor[check + sf::Vector2i(0, 1)]){
                    changing = false;
                }

                if(changing){
                    floor[check] = false;
                    grid[x][y].setFillColor(sf::Color::Transparent);
                }
            }
        }
    }

    gen++;
}

void Level::gen3(){
    //fill walls
    for(int x = 0; x < wsize; ++x){
        for(int y = 0; y < wsize; ++y){
            if(floor[sf::Vector2i(x, y)]){
                grid[x][y].setFillColor(sf::Color(50, 150, 50));
            }
            else{
                sf::Vector2i check(x, y);
                if(floor[check + sf::Vector2i(-1, -1)]
                || floor[check + sf::Vector2i(0, -1)]
                || floor[check + sf::Vector2i(1, -1)]
                || floor[check + sf::Vector2i(-1, 0)]
                || floor[check + sf::Vector2i(1, 0)]
                || floor[check + sf::Vector2i(-1, 1)]
                || floor[check + sf::Vector2i(0, 1)]
                || floor[check + sf::Vector2i(1, 1)]){
                    walls[check] = true;
                }

                if(walls[check]) grid[x][y].setFillColor(sf::Color(150, 50, 50));
            }
        }
    }

    gen++;
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    //for(const auto& it : rooms) target.draw(it, states);

    sf::FloatRect bounds = getViewBounds(target.getView());
    for(auto& ix : grid){
        for(auto& iy : ix){
            if(iy.getGlobalBounds().intersects(bounds)) target.draw(iy, states);
        }
    }
}
