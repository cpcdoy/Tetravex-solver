#pragma once

# include <string>
# include <ctype.h>
# include <fstream>
# include <cstdlib>
# include <vector>
# include <iostream>

# include "../solver/tetracell.hh"

/**
 * @brief IO Handler
 *
 **/
template<typename data_type>
class io_handler
{
  public:
    void open_file(std::string path);
    io_handler<data_type>& operator>>(data_type& data);
    unsigned int get_tetra_dim();

    bool is_finished();
    void close();

  private:
    std::ifstream file;

    bool finished = false;

    unsigned int idx = 0;
    unsigned int line_len = 0;

    //std::vector<std::vector<tetra_cell>> cells_cache;
    std::vector<tetra_cell> tmp_cells;
};

# include "io.hxx"
