#include "tetrasolver.hh"
#include <stdlib.h>

unsigned int tetra_solver::get_global_dist()
{
    this->global_dist = 0;
    for (unsigned int i = 0; i < this->grid_size; i++)
        for (unsigned int j = 0; j < this->grid_size; j++)
            this->global_dist += get_cell_dist(i, j);
    return this->global_dist;
}

unsigned int tetra_solver::get_cell_dist(int i, int j)
{
    auto cell = this->tetra_grid[i][j];
    return expected_swap_dist(cell, i, j);
}

unsigned int expected_swap_dist(tetra_cell cell, int i, int j)
{
    int cell_dist = 0;
    if (i + 1 < this->grid_size)
        cell_dist += abs(cell.up - this->tetra_grid[i + 1][j].down);
    if (i - 1 > 0)
        cell_dist += abs(cell.down - this->tetra_grid[i - 1][j].up);

    if (j + 1 < this->grid_size)
        cell_dist += abs(cell.right - this->tetra_grid[i][j + 1].left);

    if (j - 1 > 0)
        cell_dist += abs(cell.left - this->tetra_grid[i][j - 1].right);
    return cell_dist;
}

int tetra_solver::swap_prediction(int i1, int j1, int i2, int j2)
{
    tetra_cell cell1 = this->tetra_grid[i1][j1];
    tetra_cell cell2 = this->tetra_grid[i2][j2];

    unsigned int cur_dist1 = get_cell_dist(i1, j1);
    unsigned int cur_dist2 = get_cell_dist(i2, j2);

    unsigned int new_dist1 = expected_swap_dist(cell2, i1, j1);
    unsigned int new_dist2 = expected_swap_dist(cell1, i2, j2);

    int dist_variation = (cur_dist1 - new_dist1) + (cur_dist2 - new_dist2);
    return dist_variation;
}

void tetra_swap(int i1, int j1, int i2, int j2)
{
    /*auto tmp = *this->tetra_grid[i1][j1];
    *(this->tetra_grid[i1][j1]) = *(this->tetra_grid[i2][j2]);
    *(this->tetra_grid[i2][j2]) = tmp;*/
    std::swap(this->tetra_grid[i1][j1], this->tetra_grid[i2][j2])
}

int tetra_solver::try_tetra_swap()
{
    unsigned int i1 = rand() % (this->grid_size - 1);
    unsigned int j1 = rand() % (this->grid_size - 1);

    unsigned int i2 = rand() % (this->grid_size - 1);
    unsigned int j2 = rand() % (this->grid_size - 1);

    int dist_variation = swap_prediction(i1, j1, i2, j2);

    if (dist_variation < 0)

    return 0;
}
