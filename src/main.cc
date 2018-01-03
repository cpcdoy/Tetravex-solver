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
    //tetra_solver solver(std::string(argv[1]));
    tetra_solver solver(path);
    //solver.get_global_dist();
    //auto solver = new tetra_solver();

    return 0;
}
