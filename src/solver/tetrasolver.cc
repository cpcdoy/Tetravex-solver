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

    //srand(time(NULL));
    srand (static_cast <unsigned> (time(0)));

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
        cell_dist += abs(cell.down - this->tetra_grid[i + 1][j].up) > 0 ? 1 : 0;
    if (i - 1 > 0)
        cell_dist += abs(cell.up - this->tetra_grid[i - 1][j].down) > 0 ? 1 : 0;

    if (j + 1 < (int)this->grid_size)
        cell_dist += abs(cell.right - this->tetra_grid[i][j + 1].left) > 0 ? 1 : 0;

    if (j - 1 > 0)
        cell_dist += abs(cell.left - this->tetra_grid[i][j - 1].right) > 0 ? 1 : 0;
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
    std::swap(this->tetra_grid[i1][j1], this->tetra_grid[i2][j2]);
}

int tetra_solver::try_tetra_swap()
{
    unsigned int i1 = rand() % (this->grid_size);
    unsigned int j1 = rand() % (this->grid_size);

    unsigned int i2 = rand() % (this->grid_size);
    unsigned int j2 = rand() % (this->grid_size);

    auto v_tmp = this->tetra_grid;
    int d_old = get_global_dist();
    tetra_swap(i1, j1, i2, j2);
    int d_new = get_global_dist();
    if (d_new == 0)
        return 1;
    else if (d_old == 0)
    {
        this->tetra_grid = v_tmp;
        return 1;
    }

    int delta = d_new - d_old;

    //std::cout << "delta " << delta  << std::endl;
    if (delta >= 0)
    {
        this->tetra_grid = v_tmp;
        std::default_random_engine gen;
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        //float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (exp(-delta / this->T) > dist(gen))
            tetra_swap(i1, j1, i2, j2);
    }

    //pretty_print();
    return 0;
}

/*float tetra_solver::metropolis(float E_i, float E_i_1)
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
}*/

void tetra_solver::solve()
{
    float T_init = 100.f;
    this->T = T_init;
    float T_min = 1e-6f;
    float tau = 1e4f;
    float t = 0.f;

    float E_i_1 = get_global_dist();
    float E_i = 0.f;

    float max_steps = 1000000.f;

    int time = 0;
    float delta = 0.001f;
    int prec_d = 0;
    int d = 1;
    int it = 0;
    while (d != 0)
    {
        it++;
        if (try_tetra_swap() == 1)
        {
            std::cout << "Solved in " << it << " iterations" << std::endl;
            break;
        }

        prec_d = d;
        d = get_global_dist();
        if (d == prec_d)
            time++;
        else
            time = 0;

        if (time == 1000000)
        {
            time = 0;
            this->T += 1.f;

            max_steps += 100000.f;
        }

        t = t / (1.f + 2.5f * t);

        this->T *= pow((T_min / this->T), 1.f / max_steps);

    }
}

void tetra_solver::pretty_print()
{
    std::cout << "Grid: " << this->grid_size << "*" << this->grid_size << std::endl;
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
