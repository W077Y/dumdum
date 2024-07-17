#include <wlib_BLOB.hpp>
#include <stdexcept>

namespace wlib::blob
{
  void obj::handle_push_back_exception() { throw std::out_of_range("No bytes to push back"); }
  void obj::handle_push_front_exception() { throw std::out_of_range("No bytes to push front"); }

  void obj::handle_drop_back_exception() { throw std::out_of_range("No bytes to drop back"); }
  void obj::handle_drop_front_exception() { throw std::out_of_range("No bytes to drop front"); }

  std::byte obj::handle_peak_back_exception() { throw std::out_of_range("No bytes to peak back"); }
  std::byte obj::handle_peak_front_exception() { throw std::out_of_range("No bytes to peak front"); }
}    // namespace wlib::blob
