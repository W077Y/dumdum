#pragma once
#ifndef WLIB_BLOB_HPP_INCLUDED
#define WLIB_BLOB_HPP_INCLUDED

#include <bit>
#include <concepts>
#include <cstddef>
#include <span>

namespace wlib::blob
{
  template <typename T> concept ArithmeticOrByte = std::is_arithmetic_v<T> || std::is_same_v<T, std::byte>;

  class obj
  {
  public:
    constexpr obj(std::byte* begin, std::byte* end) noexcept;

    constexpr obj(std::byte* begin, std::size_t const& size) noexcept;

    template <std::size_t N> constexpr obj(std::byte (&buffer)[N]) noexcept;

    constexpr std::size_t get_total_number_of_bytes() const noexcept;
    constexpr std::size_t get_number_of_free_bytes() const noexcept;
    constexpr std::size_t get_number_of_used_bytes() const noexcept;

    void clear() noexcept;
    bool try_adjust_position(std::ptrdiff_t const& offset) noexcept;

    bool try_push_back(std::byte const& byte) noexcept;
    bool try_push_back(std::byte const* begin, std::byte const* end) noexcept;
    bool try_push_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_push_back(std::span<std::byte> const& data) noexcept;

    bool try_push_front(std::byte const& byte) noexcept;
    bool try_push_front(std::byte const* begin, std::byte const* end) noexcept;
    bool try_push_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_push_front(std::span<std::byte> const& data) noexcept;

    bool try_push_back_reverse(std::byte const& byte) noexcept;
    bool try_push_back_reverse(std::byte const* begin, std::byte const* end) noexcept;
    bool try_push_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_push_back_reverse(std::span<std::byte> const& data) noexcept;

    bool try_push_front_reverse(std::byte const& byte) noexcept;
    bool try_push_front_reverse(std::byte const* begin, std::byte const* end) noexcept;
    bool try_push_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_push_front_reverse(std::span<std::byte> const& data) noexcept;

    template <ArithmeticOrByte T> bool try_push_back(T const& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_push_front(T const& value, std::endian endian = std::endian::native) noexcept;

    constexpr bool try_peak_range(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_peak_back(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_peak_front(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;

    constexpr bool try_peak_range_reverse(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_peak_back_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_peak_front_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;

    template <ArithmeticOrByte T> bool try_peak_range(std::size_t const& offset, T& value, std::endian endian = std::endian::native) const noexcept;
    template <ArithmeticOrByte T> bool try_peak_back(T& value, std::endian endian = std::endian::native) const noexcept;
    template <ArithmeticOrByte T> bool try_peak_front(T& value, std::endian endian = std::endian::native) const noexcept;

    bool try_drop_range(std::size_t const& offset, std::size_t const& number_of_bytes = 1) noexcept;
    bool try_drop_back(std::size_t const& number_of_bytes = 1) noexcept;
    bool try_drop_front(std::size_t const& number_of_bytes = 1) noexcept;

    template <ArithmeticOrByte T> bool try_drop_range(std::size_t const& offset) noexcept;
    template <ArithmeticOrByte T> bool try_drop_back() noexcept;
    template <ArithmeticOrByte T> bool try_drop_front() noexcept;

    template <ArithmeticOrByte T> bool try_pop_range(std::size_t const& offset, T& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_pop_back(T& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_pop_front(T& value, std::endian endian = std::endian::native) noexcept;

    void push_back(std::byte const& byte);
    void push_back(std::byte const* begin, std::byte const* end);
    void push_back(std::byte const* begin, std::size_t const& number_of_bytes);
    void push_back(std::span<std::byte> const& data) noexcept;

    void drop_back(std::size_t const& number_of_bytes = 1);

    std::byte peak_back() const;

    std::byte pop_back();

    void push_front(std::byte const& byte);
    void push_front(std::byte const* begin, std::byte const* end);
    void push_front(std::byte const* begin, std::size_t const& number_of_bytes);
    void push_front(std::span<std::byte> const& data) noexcept;

    void drop_front();

    std::byte peak_front() const;

    std::byte pop_front();

    std::span<std::byte> get_blob() const;

  private:
    void p_shift_right(std::size_t const& shift);
    void p_shift_left(std::size_t const& offset, std::size_t const& shift);

    static std::size_t byte_copy(std::byte* dst, std::byte const* src, std::size_t const& size);
    static std::size_t byte_copy_reverse(std::byte* dst, std::byte const* src, std::size_t const& size);

    static void handle_push_back_exception();
    static void handle_push_front_exception();

    static void handle_drop_back_exception();
    static void handle_drop_front_exception();

    static std::byte handle_peak_back_exception();
    static std::byte handle_peak_front_exception();

    std::byte*  m_data;
    std::size_t m_size;
    std::size_t m_pos_idx = 0;
  };

  inline std::size_t obj::byte_copy(std::byte* dst, std::byte const* src, std::size_t const& size)
  {
    for (std::size_t idx = 0; idx < size; idx++)
    {
      dst[idx] = src[idx];
    }
    return size;
  }

  inline std::size_t obj::byte_copy_reverse(std::byte* dst, std::byte const* src, std::size_t const& size)
  {
    for (std::size_t idx = 0; idx < size; idx++)
    {
      dst[idx] = src[size - 1 - idx];
    }
    return size;
  }

  inline constexpr obj::obj(std::byte* begin, std::byte* end) noexcept
      : obj(begin, end - begin)
  {
  }

  inline constexpr obj::obj(std::byte* begin, std::size_t const& size) noexcept
      : m_data(begin)
      , m_size(size)
  {
  }

  template <std::size_t N>
  inline constexpr obj::obj(std::byte (&buffer)[N]) noexcept
      : obj(buffer, N)
  {
  }

  template <ArithmeticOrByte T> inline bool obj::try_push_back(T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_push_back(reinterpret_cast<std::byte const*>(&value), sizeof(value));
    else
      return this->try_push_back_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_peak_range(std::size_t const& offset, T& value, std::endian endian) const noexcept
  {
    if (endian == std::endian::native)
    {
      return this->try_peak_range(offset, reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
    else
    {
      return this->try_peak_range_reverse(offset, reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
  }

  template <ArithmeticOrByte T> inline bool obj::try_peak_back(T& value, std::endian endian) const noexcept
  {
    if (endian == std::endian::native)
    {
      return this->try_peak_back(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
    else
    {
      return this->try_peak_back_reverse(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
  }

  template <ArithmeticOrByte T> inline bool obj::try_drop_range(std::size_t const& offset) noexcept { return this->try_drop_range(offset, sizeof(T)); }

  template <ArithmeticOrByte T> inline bool obj::try_drop_back() noexcept { return this->try_drop_back(sizeof(T)); }

  template <ArithmeticOrByte T> inline bool obj::try_pop_range(std::size_t const& offset, T& value, std::endian endian) noexcept
  {
    return this->try_peak_range(offset, value, endian) && this->try_drop_back<T>(offset);
  }

  template <ArithmeticOrByte T> inline bool obj::try_pop_back(T& value, std::endian endian) noexcept
  {
    return this->try_peak_back(value, endian) && this->try_drop_back<T>();
  }

  template <ArithmeticOrByte T> inline bool obj::try_push_front(T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_push_front(reinterpret_cast<std::byte const*>(&value), sizeof(value));
    else
      return this->try_push_front_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_peak_front(T& value, std::endian endian) const noexcept
  {
    if (endian == std::endian::native)
      return this->try_peak_front(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    else
      return this->try_peak_front_reverse(reinterpret_cast<std ::byte*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_drop_front() noexcept { return this->try_drop_front(sizeof(T)); }

  template <ArithmeticOrByte T> inline bool obj::try_pop_front(T& value, std::endian endian) noexcept
  {
    return this->try_peak_front(value, endian) && this->try_drop_front<T>();
  }

  inline constexpr std::size_t obj::get_total_number_of_bytes() const noexcept { return this->m_size; }

  inline constexpr std::size_t obj::get_number_of_free_bytes() const noexcept { return this->m_size - this->m_pos_idx; }

  inline constexpr std::size_t obj::get_number_of_used_bytes() const noexcept { return this->m_pos_idx; }

  inline bool obj::try_push_back(std::byte const& byte) noexcept { return this->try_push_back(&byte, 1); }

  inline bool obj::try_push_back(std::byte const* begin, std::byte const* end) noexcept { return this->try_push_back(begin, end - begin); }

  inline bool obj::try_push_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    std::size_t const end_pos = this->m_pos_idx + number_of_bytes;
    if (end_pos >= this->m_size)
      return false;

    this->m_pos_idx += obj::byte_copy(&this->m_data[this->m_pos_idx], begin, number_of_bytes);

    return true;
  }

  inline bool obj::try_push_back(std::span<std::byte> const& data) noexcept { return this->try_push_back(data.data(), data.size_bytes()); }

  inline bool obj::try_push_back_reverse(std::byte const& byte) noexcept { return this->try_push_back_reverse(&byte, 1); }

  inline bool obj::try_push_back_reverse(std::byte const* begin, std::byte const* end) noexcept { return this->try_push_back_reverse(begin, end - begin); }

  inline bool obj::try_push_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    std::size_t const end_pos = this->m_pos_idx + number_of_bytes;
    if (end_pos >= this->m_size)
      return false;

    this->m_pos_idx += obj::byte_copy_reverse(&this->m_data[this->m_pos_idx], begin, number_of_bytes);

    return true;
  }

  inline bool obj::try_push_back_reverse(std::span<std::byte> const& data) noexcept { return this->try_push_back_reverse(data.data(), data.size_bytes()); }

  inline constexpr bool obj::try_peak_range(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    if (this->m_pos_idx < (offset + number_of_bytes))
      return false;

    obj::byte_copy(ptr, &this->m_data[offset], number_of_bytes);
    return true;
  }

  inline constexpr bool obj::try_peak_range_reverse(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    if (this->m_pos_idx < (offset + number_of_bytes))
      return false;

    obj::byte_copy_reverse(ptr, &this->m_data[offset], number_of_bytes);
    return true;
  }

  inline constexpr bool obj::try_peak_back(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_peak_range(this->m_pos_idx - number_of_bytes, ptr, number_of_bytes);
  }

  inline constexpr bool obj::try_peak_back_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_peak_range_reverse(this->m_pos_idx - number_of_bytes, ptr, number_of_bytes);
  }

  inline bool obj::try_drop_range(std::size_t const& offset, std::size_t const& number_of_bytes) noexcept
  {
    if (this->m_pos_idx < (offset + number_of_bytes))
      return false;

    this->p_shift_left(offset, number_of_bytes);
    return true;
  }

  inline bool obj::try_drop_back(std::size_t const& number_of_bytes) noexcept
  {
    if (this->m_pos_idx < number_of_bytes)
      return false;
    this->m_pos_idx -= number_of_bytes;
    return true;
  }

  inline bool obj::try_push_front(std::byte const& byte) noexcept { return this->try_push_front(&byte, 1); }

  inline bool obj::try_push_front(std::byte const* begin, std::byte const* end) noexcept { return this->try_push_front(begin, end - begin); }

  inline bool obj::try_push_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    std::size_t const end_pos = this->m_pos_idx + number_of_bytes;
    if (end_pos >= this->m_size)
      return false;

    this->p_shift_right(number_of_bytes);
    obj::byte_copy(&this->m_data[0], begin, number_of_bytes);
    return true;
  }

  inline bool obj::try_push_front(std::span<std::byte> const& data) noexcept { return this->try_push_front(data.data(), data.size_bytes()); }

  inline bool obj::try_push_front_reverse(std::byte const& byte) noexcept { return this->try_push_front_reverse(&byte, 1); }

  inline bool obj::try_push_front_reverse(std::byte const* begin, std::byte const* end) noexcept { return this->try_push_front_reverse(begin, end - begin); }

  inline bool obj::try_push_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    std::size_t const end_pos = this->m_pos_idx + number_of_bytes;
    if (end_pos >= this->m_size)
      return false;

    this->p_shift_right(number_of_bytes);
    obj::byte_copy_reverse(&this->m_data[0], begin, number_of_bytes);
    return true;
  }

  inline bool obj::try_push_front_reverse(std::span<std::byte> const& data) noexcept { return this->try_push_front_reverse(data.data(), data.size_bytes()); }

  inline constexpr bool obj::try_peak_front(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_peak_range(0, ptr, number_of_bytes);
  }

  inline constexpr bool obj::try_peak_front_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_peak_range_reverse(0, ptr, number_of_bytes);
  }

  inline bool obj::try_drop_front(std::size_t const& number_of_bytes) noexcept
  {
    if (this->m_pos_idx < number_of_bytes)
      return false;
    this->p_shift_left(0, number_of_bytes);
    return true;
  }

  inline void obj::push_back(std::byte const& byte)
  {
    if (!this->try_push_back(byte))
      return obj::handle_push_back_exception();
  }

  inline void obj::push_back(std::byte const* begin, std::byte const* end)
  {
    if (!this->try_push_back(begin, end))
      return obj::handle_push_back_exception();
  }

  inline void obj::push_back(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_push_back(begin, number_of_bytes))
      return obj::handle_push_back_exception();
  }

  inline void obj::push_back(std::span<std::byte> const& data) noexcept
  {
    if (!this->try_push_back(data))
      return obj::handle_push_back_exception();
  }

  inline void obj::drop_back(std::size_t const& number_of_bytes)
  {
    if (!this->try_drop_back(number_of_bytes))
      return obj::handle_drop_back_exception();
  }

  inline std::byte obj::peak_back() const
  {
    std::byte val{};
    if (!this->try_peak_back(val))
      return obj::handle_peak_back_exception();
    return val;
  }

  inline std::byte obj::pop_back()
  {
    std::byte tmp = this->peak_back();
    this->drop_back();
    return tmp;
  }

  inline void obj::push_front(std::byte const& byte)
  {
    if (!this->try_push_front(byte))
      return handle_push_front_exception();
  }

  inline void obj::push_front(std::byte const* begin, std::byte const* end)
  {
    if (!this->try_push_front(begin, end))
      return obj::handle_push_back_exception();
  }

  inline void obj::push_front(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_push_front(begin, number_of_bytes))
      return obj::handle_push_back_exception();
  }

  inline void obj::push_front(std::span<std::byte> const& data) noexcept
  {
    if (!this->try_push_front(data))
      return obj::handle_push_back_exception();
  }

  inline void obj::drop_front()
  {
    if (this->try_drop_front())
      return handle_drop_front_exception();
  }

  inline std::byte obj::peak_front() const
  {
    std::byte val{};
    if (!this->try_peak_front(val))
      return obj::handle_peak_front_exception();
    return val;
  }

  inline std::byte obj::pop_front()
  {
    std::byte tmp = this->peak_front();
    this->drop_front();
    return tmp;
  }

  inline std::span<std::byte> obj::get_blob() const { return std::span<std::byte>(this->m_data, this->m_pos_idx); }

  inline void obj::clear() noexcept { this->m_pos_idx = 0; }

  inline bool obj::try_adjust_position(std::ptrdiff_t const& offset) noexcept
  {
    if ((offset > 0) && (this->m_pos_idx + offset) > this->m_size)
      return false;
    if ((offset < 0) && (this->m_pos_idx < offset))
      return false;

    this->m_pos_idx += offset;
    return true;
  }

  inline void obj::p_shift_right(std::size_t const& shift)
  {
    for (std::size_t i = this->m_pos_idx + shift; i > shift;)
    {
      --i;
      this->m_data[i] = this->m_data[i - shift];
    }
    this->m_pos_idx += shift;
  }

  inline void obj::p_shift_left(std::size_t const& offset, std::size_t const& shift)
  {
    for (std::size_t i = offset; i < this->m_pos_idx - shift; i++)
    {
      this->m_data[i] = this->m_data[i + shift];
    }
    this->m_pos_idx -= shift;
  }
}    // namespace wlib::blob

#endif    // !WLIB_CRC_INTERFACE_HPP
