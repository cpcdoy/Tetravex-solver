#include <iostream>

#include "utils/io.hh"
#include "solver/tetrasolver.hh"

/**
 * @brief Tetravex solver entry point (main)
 *
 * @param argc
 * @param argv
 *
 * @return
 **/
int main(int argc, char** argv)
{
    io_handler<tetra_cell> cell_io;
    cell_io.open_file(argv[1]);
    while (!cell_io.is_finished())
    {
        tetra_cell c;
        cell_io >> c;
        if (c.up != -1)
        {
            std::cout << "tetra dim " << cell_io.get_tetra_dim() << std::endl;
            std::cout << c.up << std::endl;
            std::cout << c.left << " " << c.right << std::endl;
            std::cout << c.down << std::endl;
        }
    }

    return 0;
}
