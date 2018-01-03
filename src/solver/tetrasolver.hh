#pragma once
#include "tetracell.hh"
#include <vector>

class tetra_solver
{
    private:
        std::vector<std::vector<tetra_cell> tetra_grid;
        double temperature;
        unsigned int global_dist;
};
