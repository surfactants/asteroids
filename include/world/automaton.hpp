#pragma once

#include <map>
#include <SFML/System/Vector2.hpp>

using Adjacency_Rules = std::map<unsigned int, float>;
using Cells = std::map<int, std::map<int, bool>>;

class Automaton{
public:
    Automaton(Cells ncells, unsigned int niterations, Adjacency_Rules nadj_take, Adjacency_Rules nadj_add);

    Cells iterate();

private:
    Cells cells;

    unsigned int iterations;

    Adjacency_Rules adj_take;
    Adjacency_Rules adj_add;

    sf::Vector2i min{ 0, 0 };
    sf::Vector2i max{ 0, 0 };

    unsigned int countAdjacentActiveCells(int x, int y);
    bool defined(int x, int y);
};
