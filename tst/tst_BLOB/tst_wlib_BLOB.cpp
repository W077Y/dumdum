#include <concepts>
#include <cstddef>
#include <iostream>
#include <span>
#include <stdexcept>
#include <ut_catch.hpp>
#include <wlib_BLOB.hpp>

namespace wlib::blob
{
  class obj
  {
  public:
    constexpr obj(std::byte* begin, std::byte* end) noexcept
        : obj(begin, end - begin)
    {
    }

    constexpr obj(std::byte* begin, std::size_t const& size) noexcept
        : m_data(begin)
        , m_size(size)
    {
    }

    template <std::size_t N>
    constexpr obj(std::byte (&buffer)[N]) noexcept
        : obj(buffer, N)
    {
    }

    constexpr std::size_t get_total_number_of_bytes() const noexcept { return this->m_size; }

    constexpr std::size_t get_number_of_free_bytes() const noexcept { return this->m_size - this->m_pos_idx; }

    constexpr std::size_t get_number_of_used_bytes() const noexcept { return this->m_pos_idx; }

    bool try_push_back(std::byte const& byte) noexcept { return this->try_push_back(&byte, 1); }
    bool try_push_back(std::byte const* begin, std::byte const* end) noexcept { return this->try_push_back(begin, end - begin); }
    bool try_push_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
    {
      std::size_t const end_pos = this->m_pos_idx + number_of_bytes;
      if (end_pos >= this->m_size)
        return false;

      for (std::size_t idx = 0; idx < number_of_bytes;)
        this->m_data[this->m_pos_idx++] = begin[idx++];

      return true;
    }
    bool try_push_back(std::span<std::byte> const& data) noexcept { return this->try_push_back(data.data(), data.size_bytes()); }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_push_back(T const& value) noexcept
    {
      return this->try_push_back(reinterpret_cast<std::byte const*>(&value), sizeof(value));
    }

    constexpr bool try_peak_back(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
    {
      if (this->m_pos_idx < number_of_bytes)
        return false;

      std::memcpy(ptr, &this->m_data[this->m_pos_idx - number_of_bytes], number_of_bytes);
      return true;
    }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_peak_back(T& value) const noexcept
    {
      return this->try_peak_back(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }

    bool try_drop_back(std::size_t const& number_of_bytes = 1) noexcept
    {
      if (this->m_pos_idx < number_of_bytes)
        return false;
      this->m_pos_idx -= number_of_bytes;
      return true;
    }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_drop_back() noexcept
    {
      return this->try_drop_back(sizeof(T));
    }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_pop_back(T& value) noexcept
    {
      return this->try_peak_back(value) && this->try_drop_back<T>();
    }

    bool try_push_front(std::byte const& byte) noexcept { return this->try_push_front(&byte, 1); }
    bool try_push_front(std::byte const* begin, std::byte const* end) noexcept { return this->try_push_front(begin, end - begin); }
    bool try_push_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
    {
      std::size_t const end_pos = this->m_pos_idx + number_of_bytes;
      if (end_pos >= this->m_size)
        return false;

      this->p_shift_right(number_of_bytes);

      for (std::size_t idx = 0; idx < number_of_bytes;)
        this->m_data[idx] = begin[idx++];
      return true;
    }
    bool try_push_front(std::span<std::byte> const& data) noexcept { return this->try_push_front(data.data(), data.size_bytes()); }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_push_front(T const& value) noexcept
    {
      return this->try_push_front(reinterpret_cast<std::byte const*>(&value), sizeof(value));
    }

    constexpr bool try_peak_front(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
    {
      if (this->m_pos_idx < number_of_bytes)
        return false;

      std::memcpy(ptr, &this->m_data[0], number_of_bytes);
      return true;
    }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_peak_front(T& value) const noexcept
    {
      return this->try_peak_front(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }

    bool try_drop_front(std::size_t const& number_of_bytes = 1) noexcept
    {
      if (this->m_pos_idx < number_of_bytes)
        return false;
      this->p_shift_left(number_of_bytes);
      return true;
    }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_drop_front() noexcept
    {
      return this->try_drop_front(sizeof(T));
    }

    template <typename T> requires(std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>) bool try_pop_front(T& value) noexcept
    {
      return this->try_peak_front(value) && this->try_drop_front<T>();
    }

    void push_back(std::byte const& byte)
    {
      if (!this->try_push_back(byte))
        return obj::handle_push_back_exception();
    }
    void push_back(std::byte const* begin, std::byte const* end)
    {
      if (!this->try_push_back(begin, end))
        return obj::handle_push_back_exception();
    }
    void push_back(std::byte const* begin, std::size_t const& number_of_bytes)
    {
      if (!this->try_push_back(begin, number_of_bytes))
        return obj::handle_push_back_exception();
    }
    void push_back(std::span<std::byte> const& data) noexcept
    {
      if (!this->try_push_back(data))
        return obj::handle_push_back_exception();
    }

    void drop_back(std::size_t const& number_of_bytes = 1)
    {
      if (!this->try_drop_back(number_of_bytes))
        return obj::handle_drop_back_exception();
    }

    std::byte peak_back() const
    {
      std::byte val{};
      if (!this->try_peak_back(val))
        return obj::handle_peak_back_exception();
      return val;
    }

    std::byte pop_back()
    {
      std::byte tmp = this->peak_back();
      this->drop_back();
      return tmp;
    }

    void push_front(std::byte const& byte)
    {
      if (!this->try_push_front(byte))
        return handle_push_front_exception();
    }
    void push_front(std::byte const* begin, std::byte const* end)
    {
      if (!this->try_push_front(begin, end))
        return obj::handle_push_back_exception();
    }
    void push_front(std::byte const* begin, std::size_t const& number_of_bytes)
    {
      if (!this->try_push_front(begin, number_of_bytes))
        return obj::handle_push_back_exception();
    }
    void push_front(std::span<std::byte> const& data) noexcept
    {
      if (!this->try_push_front(data))
        return obj::handle_push_back_exception();
    }

    void drop_front()
    {
      if (this->try_drop_front())
        return handle_drop_front_exception();
    }

    std::byte peak_front() const
    {
      std::byte val{};
      if (!this->try_peak_front(val))
        return obj::handle_peak_front_exception();
      return val;
    }

    std::byte pop_front()
    {
      std::byte tmp = this->peak_front();
      this->drop_front();
      return tmp;
    }

    std::span<std::byte> get_blob() const { return std::span<std::byte>(this->m_data, this->m_pos_idx); }

    void clear() noexcept { this->m_pos_idx = 0; }

  private:
    void p_shift_right(std::size_t const& shift)
    {
      for (std::size_t i = this->m_pos_idx + shift; i > shift;)
      {
        --i;
        this->m_data[i] = this->m_data[i - shift];
      }
      this->m_pos_idx += shift;
    }

    void p_shift_left(std::size_t const& shift)
    {
      for (std::size_t i = 0; i < this->m_pos_idx; i++)
      {
        this->m_data[i] = this->m_data[i + shift];
      }
      this->m_pos_idx -= shift;
    }

    static void handle_push_back_exception() { throw std::out_of_range("No bytes to push back"); }
    static void handle_push_front_exception() { throw std::out_of_range("No bytes to push front"); }

    static void handle_drop_back_exception() { throw std::out_of_range("No bytes to drop back"); }
    static void handle_drop_front_exception() { throw std::out_of_range("No bytes to drop front"); }

    static std::byte handle_peak_back_exception() { throw std::out_of_range("No bytes to peak back"); }
    static std::byte handle_peak_front_exception() { throw std::out_of_range("No bytes to peak front"); }

    std::byte*  m_data;
    std::size_t m_size;
    std::size_t m_pos_idx = 0;
  };
}    // namespace wlib::blob

void print_buffer(wlib::blob::obj const& blob, std::span<std::byte> const& buffer)
{
  for (std::byte entry : blob.get_blob())
  {
    std::cout << static_cast<int>(entry) << ", ";
  }
  std::cout << std::endl;
  for (std::byte entry : buffer)
  {
    std::cout << static_cast<int>(entry) << ", ";
  }
  std::cout << std::endl;
}

TEST_CASE()
{
  std::byte buffer[30]{};

  wlib::blob::obj blob{ buffer };

  REQUIRE(blob.get_total_number_of_bytes() == 30);
  REQUIRE(blob.get_number_of_free_bytes() == 30);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  blob.push_back(static_cast<std::byte>(0x03));
  blob.push_back(static_cast<std::byte>(0x04));
  blob.push_front(static_cast<std::byte>(0x02));
  blob.push_front(static_cast<std::byte>(0x01));

  REQUIRE(blob.get_total_number_of_bytes() == 30);
  REQUIRE(blob.get_number_of_free_bytes() == 26);
  REQUIRE(blob.get_number_of_used_bytes() == 4);

  blob.clear();

  REQUIRE(blob.get_total_number_of_bytes() == 30);
  REQUIRE(blob.get_number_of_free_bytes() == 30);
  REQUIRE(blob.get_number_of_used_bytes() == 0);
}

TEST_CASE()
{
  static constexpr std::size_t buffer_size = 1 + sizeof(std::byte) + sizeof(char) + sizeof(signed char) + sizeof(unsigned char) + sizeof(char8_t) +
                                             sizeof(char16_t) + sizeof(char32_t) + sizeof(signed short) + sizeof(unsigned short) + sizeof(signed int) +
                                             sizeof(unsigned int) + sizeof(signed long) + sizeof(unsigned long) + sizeof(signed long long) +
                                             sizeof(unsigned long long) + sizeof(float) + sizeof(double) + sizeof(long double);

  std::byte buffer[buffer_size]{};

  wlib::blob::obj blob{ buffer };

  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  bool ret = true;
  ret &= blob.try_push_back(static_cast<std::byte>(0x01));
  ret &= blob.try_push_back(static_cast<char>(0x02));
  ret &= blob.try_push_back(static_cast<signed char>(0x03));
  ret &= blob.try_push_back(static_cast<unsigned char>(0x04));
  ret &= blob.try_push_back(static_cast<char8_t>(0x05));
  ret &= blob.try_push_back(static_cast<char16_t>(0x06));
  ret &= blob.try_push_back(static_cast<char32_t>(0x07));
  ret &= blob.try_push_back(static_cast<signed short>(0x08));
  ret &= blob.try_push_back(static_cast<unsigned short>(0x09));
  ret &= blob.try_push_back(static_cast<signed int>(0x0A));
  ret &= blob.try_push_back(static_cast<unsigned int>(0x0B));
  ret &= blob.try_push_back(static_cast<signed long>(0x0C));
  ret &= blob.try_push_back(static_cast<unsigned long>(0x0D));
  ret &= blob.try_push_back(static_cast<signed long long>(0x0E));
  ret &= blob.try_push_back(static_cast<unsigned long long>(0x0F));
  ret &= blob.try_push_back(static_cast<float>(0x10));
  ret &= blob.try_push_back(static_cast<double>(0x11));
  ret &= blob.try_push_back(static_cast<long double>(0x12));

  REQUIRE(ret);
  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == 1);
  REQUIRE(blob.get_number_of_used_bytes() == buffer_size - 1);
  REQUIRE_FALSE(blob.try_push_back(static_cast<long double>(0x13)));

  long double        val_long_double;
  double             val_double;
  float              val_float;
  unsigned long long val_unsigned_long_long;
  signed long long   val_signed_long_long;
  unsigned long      val_unsigned_long;
  signed long        val_signed_long;
  unsigned int       val_unsigned_int;
  signed int         val_signed_int;
  unsigned short     val_unsigned_short;
  signed short       val_signed_short;
  char32_t           val_char32_t;
  char16_t           val_char16_t;
  char8_t            val_char8_t;
  unsigned char      val_unsigned_char;
  signed char        val_signed_char;
  char               val_char;
  std::byte          val_byte;

  ret &= blob.try_pop_back(val_long_double);
  ret &= blob.try_pop_back(val_double);
  ret &= blob.try_pop_back(val_float);
  ret &= blob.try_pop_back(val_unsigned_long_long);
  ret &= blob.try_pop_back(val_signed_long_long);
  ret &= blob.try_pop_back(val_unsigned_long);
  ret &= blob.try_pop_back(val_signed_long);
  ret &= blob.try_pop_back(val_unsigned_int);
  ret &= blob.try_pop_back(val_signed_int);
  ret &= blob.try_pop_back(val_unsigned_short);
  ret &= blob.try_pop_back(val_signed_short);
  ret &= blob.try_pop_back(val_char32_t);
  ret &= blob.try_pop_back(val_char16_t);
  ret &= blob.try_pop_back(val_char8_t);
  ret &= blob.try_pop_back(val_unsigned_char);
  ret &= blob.try_pop_back(val_signed_char);
  ret &= blob.try_pop_back(val_char);
  ret &= blob.try_pop_back(val_byte);

  REQUIRE(val_long_double == static_cast<long double>(0x12));
  REQUIRE(val_double == static_cast<double>(0x11));
  REQUIRE(val_float == static_cast<float>(0x10));
  REQUIRE(val_unsigned_long_long == static_cast<unsigned long long>(0x0F));
  REQUIRE(val_signed_long_long == static_cast<signed long long>(0x0E));
  REQUIRE(val_unsigned_long == static_cast<unsigned long>(0x0D));
  REQUIRE(val_signed_long == static_cast<signed long>(0x0C));
  REQUIRE(val_unsigned_int == static_cast<unsigned int>(0x0B));
  REQUIRE(val_signed_int == static_cast<signed int>(0x0A));
  REQUIRE(val_unsigned_short == static_cast<unsigned short>(0x09));
  REQUIRE(val_signed_short == static_cast<signed short>(0x08));
  REQUIRE(val_char32_t == static_cast<char32_t>(0x07));
  REQUIRE(val_char16_t == static_cast<char16_t>(0x06));
  REQUIRE(val_char8_t == static_cast<char8_t>(0x05));
  REQUIRE(val_unsigned_char == static_cast<unsigned char>(0x04));
  REQUIRE(val_signed_char == static_cast<signed char>(0x03));
  REQUIRE(val_char == static_cast<char>(0x02));
  REQUIRE(val_byte == static_cast<std::byte>(0x01));

  REQUIRE(ret);
  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  REQUIRE(blob.try_push_back(static_cast<long long>(0x13)));

  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == buffer_size - sizeof(long long));
  REQUIRE(blob.get_number_of_used_bytes() == sizeof(long long));
}
