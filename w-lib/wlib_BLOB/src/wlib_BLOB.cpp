#include "wlib_BLOB.hpp"

#include <stdexcept>
#include <wlib_BLOB.hpp>

namespace wlib::blob
{
  void obj::handle_overwrite_exception() { throw std::out_of_range("not enouth room to insert object"); }
  void obj::handle_insert_exception() { throw std::out_of_range("not enouth room to insert object"); }
  void obj::handle_remove_exception() { throw std::out_of_range("not enouth bytes left"); }
  void obj::handle_read_exception() { throw std::out_of_range("not enouth bytes left to read"); }
}    // namespace wlib::blob
