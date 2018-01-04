#include "tetrasolver.hh"
#include <stdlib.h>

tetra_solver::tetra_solver(std::string path)
{
    io_handler<tetra_cell> cell_io;
    cell_io.open_file(path);

    tetra_cell c;
    cell_io >> c;
    this->grid_size = cell_io.get_tetra_dim();

    std::vector<tetra_cell> tmp_cells;
    while (!cell_io.is_finished())
    {
        tetra_cell c;
        cell_io >> c;
    }
    this->tetra_grid = cell_io.get_cells();
}

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

unsigned int tetra_solver::expected_swap_dist(tetra_cell cell, int i, int j)
{
    int cell_dist = 0;
    if (i + 1 < (int)this->grid_size)
        cell_dist += abs(cell.down - this->tetra_grid[i + 1][j].up);
    if (i - 1 > 0)
        cell_dist += abs(cell.up - this->tetra_grid[i - 1][j].down);

    if (j + 1 < (int)this->grid_size)
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

void tetra_solver::tetra_swap(int i1, int j1, int i2, int j2)
{
    /*auto tmp = *this->tetra_grid[i1][j1];
    *(this->tetra_grid[i1][j1]) = *(this->tetra_grid[i2][j2]);
    *(this->tetra_grid[i2][j2]) = tmp;*/
    //std::cout << "swapping " << i1 << " " << j1 << " " << i2 << " " << j2 << std::endl;
    std::swap(this->tetra_grid[i1][j1], this->tetra_grid[i2][j2]);
}

int tetra_solver::try_tetra_swap()
{
    unsigned int i1 = rand() % (this->grid_size);
    unsigned int j1 = rand() % (this->grid_size);

    unsigned int i2 = rand() % (this->grid_size);
    unsigned int j2 = rand() % (this->grid_size);

    int dist_variation = swap_prediction(i1, j1, i2, j2);

    //std::cout << "dist var " << dist_variation << std::endl;
    tetra_swap(i1, j1, i2, j2);
    //pretty_print();
    return get_global_dist();
}

float tetra_solver::metropolis(float E_i, float E_i_1)
{
    if (E_i <= E_i_1)
        return E_i;
    else
    {
        const float k_b = 1.f;
        float p = exp(-(E_i - E_i_1) / (k_b * this->T));

        std::default_random_engine gen;
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        float rand = dist(gen);
        if (rand > p)
            try_tetra_swap();
    }

    return E_i_1;
}

void tetra_solver::solve()
{
    float T_init = 10.f;
    this->T = T_init;
    float T_min = 1e-4f;
    float tau = 1e4f;
    float t = 0.f;

    float E_i_1 = get_global_dist();
    float E_i = 0.f;

    int i = 0;
    while (get_global_dist() != 0)
    {
        E_i = try_tetra_swap();

        E_i_1 = metropolis(E_i, E_i_1);

        if (i++ % 100 == 0)
        {
            t += 1.f;

            this->T = T_init * sqrt(-t / tau);
        }
    }
}

void tetra_solver::pretty_print()
{
    for (unsigned int i = 0; i < this->grid_size; i++)
        for (int k = 0; k < 3; k++)
        {
            for (unsigned int j = 0; j < this->grid_size; j++)
            {
                if (k == 0)
                {
                    tetra_cell c = this->tetra_grid[i][j];
                    std::cout << " " << c.up << "  ";
                }
                else if (k == 1)
                {
                    tetra_cell c = this->tetra_grid[i][j];
                    std::cout << c.left << " " << c.right << " ";
                }
                else if (k == 2)
                {
                    tetra_cell c = this->tetra_grid[i][j];
                    std::cout << " " << c.down << "  ";
                }
            }
            std::cout << std::endl;
        }
}
