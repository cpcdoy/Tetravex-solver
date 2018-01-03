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
  return file.eof();
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
