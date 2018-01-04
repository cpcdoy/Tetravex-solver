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
    if (argc > 1)
    {
        std::string path(argv[1]);
        tetra_solver solver(path);
        solver.pretty_print();
        solver.solve();
        std::cout << "----\nSolving....\n----"<< std::endl;
        solver.pretty_print();
    }
    else
        std::cout << "--------Tetravex---------\nUsage: tetravex path/to/file" << std::endl;

    return 0;
}
