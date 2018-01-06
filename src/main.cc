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
        std::string path(argv[1 + (int)(argv[1][1] == 'n')]);
        tetra_solver solver(path, argv[1][1] == 'n');
        bool nice = argv[1][1] == 'n';
        if (nice)
        {
            solver.pretty_print();
            std::cout << "----\nSolving...." << std::endl;
        }
        solver.solve();
        if (nice)
            std::cout << "----" << std::endl;
        solver.pretty_print();
    }
    else
        std::cout << "--------Tetravex---------\nUsage: tetravex [-n] path/to/file" << std::endl;

    return 0;
}
