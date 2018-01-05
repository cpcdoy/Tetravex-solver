#pragma once

# include <string>
# include <ctype.h>
# include <fstream>
# include <cstdlib>
# include <vector>
# include <iostream>
# include <math.h>

# include "../solver/tetracell.hh"

/**
 * @brief IO Handler
 *
 **/
template<typename data_type>
class io_handler
{
  public:
    inline void open_file(std::string path);
    inline io_handler<data_type>& operator>>(data_type& data);
    inline unsigned int get_tetra_dim();
    inline std::vector<std::vector<tetra_cell>> get_cells();

    inline bool is_finished();
    inline void close();

    inline void enable_nice_format();

  private:
    std::ifstream file;

    bool finished = false;

    unsigned int idx = 0;
    unsigned int line_len = 0;

    std::vector<std::vector<tetra_cell>> cells_cache;
    std::vector<tetra_cell> tmp_cells;

    bool nice_format = false;
};

# include "io.hxx"
