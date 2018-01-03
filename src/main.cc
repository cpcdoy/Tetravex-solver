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
    while (!cell_io.is_finished())
    {
        tetra_cell c;
        cell_io >> c;
    }

    return 0;
}
