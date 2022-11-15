#include <util/prng.hpp>
#include <world/automaton.hpp>

Automaton::Automaton(Cells ncells,
    unsigned int niterations,
    Adjacency_Rules nadj_take,
    Adjacency_Rules nadj_add)
    : cells { ncells }
    , iterations { niterations }
    , adj_take { nadj_take }
    , adj_add { nadj_add }
{
    min.x = cells.begin()->first;
    max.x = cells.rbegin()->first;

    min.y = INT_MAX;
    max.y = INT_MIN;

    for (auto& c : cells) {
        if (c.second.begin()->first < min.y) {
            min.y = c.second.begin()->first;
        }
        if (c.second.rbegin()->first > max.y) {
            max.y = c.second.rbegin()->first;
        }
    }
}

Cells Automaton::iterate()
{
    Cells newCells = cells;

    for (unsigned int i = 0; i < iterations; ++i) {
        for (int x = min.x; x <= max.x; ++x) {
            for (int y = min.y; y <= max.y; ++y) {
                if (defined(x, y)) {
                    int count = countAdjacentActiveCells(x, y);
                    if (cells[x][y] && prng::boolean(adj_take[count])) {
                        newCells[x][y] = false;
                    }
                    else if (!cells[x][y] && prng::boolean(adj_add[count])) {
                        newCells[x][y] = true;
                    }
                }
            }
        }
        cells = newCells;
    }

    return cells;
}

unsigned int Automaton::countAdjacentActiveCells(int x, int y)
{
    unsigned int count { 0 };
    for (int ix = x - 1; ix <= x + 1; ++ix) {
        for (int iy = y - 1; iy <= y + 1; ++iy) {
            if (ix == x && iy == y) {
                continue;
            }

            if (defined(ix, iy) && cells[ix][iy]) {
                count++;
            }
        }
    }

    return count;
}

bool Automaton::defined(int x, int y)
{
    return (cells.count(x) && cells[x].count(y));
}
