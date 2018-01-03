#include <iostream>

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
    std::string path(argv[1]);
    tetra_solver solver(path);
    std::cout << solver.get_global_dist() << std::endl;

    return 0;
}
