# Tetravex-solver

Tetravex Solver using simulated annealing and a few tricks of our own.

It was tested on puzzles up to 6x6 but it should be able to do more given some more time.

## Build

This project is using the CMake build system.

### In-Source build

```sh
cmake .
make
```

### Out-of-Source build

```sh
mkdir build && cd build
cmake ..
make
```

## Usage

```
./tetravex [-n] path/to/file
```

The "-n" option enables to read a file format that is nicer. Every file in the data/ directory should use the "-n" option except for the files named "example*"
