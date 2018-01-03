#pragma once

# include "../utils/io.hh"

# include <vector>

class tetra_solver
{
    public:
        tetra_solver() {  }
        tetra_solver(std::string path);

        unsigned int get_global_dist();
        unsigned int get_cell_dist(int i, int j);
        unsigned int expected_swap_dist(tetra_cell cell, int i, int j);
        int swap_prediction(int i1, int j1, int i2, int j2);
        void tetra_swap(int i1, int j1, int i2, int j2);
        int try_tetra_swap();

    private:
        std::vector<std::vector<tetra_cell>> tetra_grid;
        unsigned int grid_size;
        unsigned int global_dist;
        double temperature;
};
