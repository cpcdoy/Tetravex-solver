#include "io.hh"

/**
 * @brief
 *
 * @param path
 *
 * @return
 */
template<typename data_type>
void
io_handler<data_type>::
open_file(std::string path)
{
    file.open(path.c_str(), std::ios::in);
}

/**
 * @brief
 *
 * @return
 */
template<typename data_type>
bool
io_handler<data_type>::
is_finished()
{
    return file.eof() || finished;
}

/**
 * @brief
 *
 * @param line
 *
 * @return
 */
template<typename data_type>
io_handler<data_type>&
io_handler<data_type>::
operator>>(data_type& line)
{
    return *this;
}

/**
 * @brief
 *
 * @param line
 *
 * @return
 */
template<>
unsigned int
io_handler<tetra_cell>::
get_tetra_dim()
{
    return line_len;
}

/**
 * @brief
 *
 * @param line
 *
 * @return
 */
template<>
io_handler<tetra_cell>&
io_handler<tetra_cell>::
operator>>(tetra_cell& cell)
{
    std::string line;

    if (idx == 0 || idx % line_len == 0)
    {
        tmp_cells.clear();
        // First line : UP
        if (!std::getline(file, line))
        {
            finished = true;
            cell.up = -1;

            return *this;
        }

        std::string::iterator it;
        for (it = line.begin(); it != line.end(); it++)
            if (!isspace(*it))
            {
                if (idx == 0)
                    line_len++;
                tetra_cell c;
                c.up = *it - '0';
                tmp_cells.push_back(c);
            }

        // 2nd line : LEFT RIGHT
        if (!std::getline(file, line))
        {
            finished = true;
            cell.left = -1;

            std::cerr << "Error when parsing the LEFT/RIGHT element of the cell." << std::endl;
            return *this;
        }

        int j = 0;
        it = line.begin();
        for (int i = 0; it != line.end(); it++)
            if (!isspace(*it))
            {
                tetra_cell& c = tmp_cells[j];
                if (i++ % 2 == 0)
                    c.left = *it - '0';
                else
                {
                    c.right = *it - '0';
                    j++;
                }
            }
        // 3rd line : DOWN
        if (!std::getline(file, line))
        {
            finished = true;
            cell.down = -1;

            std::cerr << "Error when parsing the DOWN element of the cell." << std::endl;
            return *this;
        }

        j = 0;
        for (it = line.begin(); it != line.end(); it++)
            if (!isspace(*it))
            {
                tetra_cell& c = tmp_cells[j++];
                c.down = *it - '0';
            }

        // Return the next cell
        cell = tmp_cells[0];
        idx++;
    }
    else
        cell = tmp_cells[idx++ % line_len];


    return *this;
}

/**
 * @brief
 *
 * @param line
 *
 * @return
 */
template<>
io_handler<std::string>&
io_handler<std::string>::
operator>>(std::string& line)
{
    std::getline(file, line);
    return *this;
}

/**
 * @brief
 *
 * @return
 */
template<typename data_type>
void
io_handler<data_type>::
close()
{
    file.close();
}
