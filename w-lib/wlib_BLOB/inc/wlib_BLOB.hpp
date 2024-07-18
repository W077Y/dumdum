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
    constexpr obj(std::byte* begin, std::byte* end, std::byte* position) noexcept;
    constexpr obj(std::byte* begin, std::size_t const& size, std::size_t const& position_idx = 0) noexcept;

    template <std::size_t N> constexpr obj(std::byte (&buffer)[N], std::size_t const& position_idx = 0) noexcept;

    [[nodiscard]] constexpr std::size_t          get_total_number_of_bytes() const noexcept;
    [[nodiscard]] constexpr std::size_t          get_number_of_free_bytes() const noexcept;
    [[nodiscard]] constexpr std::size_t          get_number_of_used_bytes() const noexcept;
    [[nodiscard]] constexpr std::span<std::byte> get_blob() const noexcept;
    constexpr void                               clear() noexcept;
    constexpr bool                               try_adjust_position(std::ptrdiff_t const& offset) noexcept;
    constexpr bool                               try_set_position(std::size_t const& position) noexcept;

    bool try_overwrite(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept;

    bool try_overwrite(std::size_t const& offset, std::byte const& byte) noexcept;
    bool try_overwrite(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept;
    bool try_overwrite(std::size_t const& offset, std::span<std::byte> const& data) noexcept;
    bool try_overwrite_back(std::byte const& byte) noexcept;
    bool try_overwrite_back(std::byte const* begin, std::byte const* end) noexcept;
    bool try_overwrite_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_overwrite_back(std::span<std::byte> const& data) noexcept;
    bool try_overwrite_front(std::byte const& byte) noexcept;
    bool try_overwrite_front(std::byte const* begin, std::byte const* end) noexcept;
    bool try_overwrite_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_overwrite_front(std::span<std::byte> const& data) noexcept;

    bool try_overwrite_reverse(std::size_t const& offset, std::byte const& byte) noexcept;
    bool try_overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept;
    bool try_overwrite_reverse(std::size_t const& offset, std::span<std::byte> const& data) noexcept;
    bool try_overwrite_back_reverse(std::byte const& byte) noexcept;
    bool try_overwrite_back_reverse(std::byte const* begin, std::byte const* end) noexcept;
    bool try_overwrite_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_overwrite_back_reverse(std::span<std::byte> const& data) noexcept;
    bool try_overwrite_front_reverse(std::byte const& byte) noexcept;
    bool try_overwrite_front_reverse(std::byte const* begin, std::byte const* end) noexcept;
    bool try_overwrite_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_overwrite_front_reverse(std::span<std::byte> const& data) noexcept;

    template <ArithmeticOrByte T> bool try_overwrite(std::size_t const& offset, T const& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_overwrite_back(T const& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_overwrite_front(T const& value, std::endian endian = std::endian::native) noexcept;

    bool try_insert(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_insert_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept;

    bool try_insert(std::size_t const& offset, std::byte const& byte) noexcept;
    bool try_insert(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept;
    bool try_insert(std::size_t const& offset, std::span<std::byte> const& data) noexcept;
    bool try_insert_back(std::byte const& byte) noexcept;
    bool try_insert_back(std::byte const* begin, std::byte const* end) noexcept;
    bool try_insert_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_insert_back(std::span<std::byte> const& data) noexcept;
    bool try_insert_front(std::byte const& byte) noexcept;
    bool try_insert_front(std::byte const* begin, std::byte const* end) noexcept;
    bool try_insert_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_insert_front(std::span<std::byte> const& data) noexcept;

    bool try_insert_reverse(std::size_t const& offset, std::byte const& byte) noexcept;
    bool try_insert_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept;
    bool try_insert_reverse(std::size_t const& offset, std::span<std::byte> const& data) noexcept;
    bool try_insert_back_reverse(std::byte const& byte) noexcept;
    bool try_insert_back_reverse(std::byte const* begin, std::byte const* end) noexcept;
    bool try_insert_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_insert_back_reverse(std::span<std::byte> const& data) noexcept;
    bool try_insert_front_reverse(std::byte const& byte) noexcept;
    bool try_insert_front_reverse(std::byte const* begin, std::byte const* end) noexcept;
    bool try_insert_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept;
    bool try_insert_front_reverse(std::span<std::byte> const& data) noexcept;

    template <ArithmeticOrByte T> bool try_insert(std::size_t const& offset, T const& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_insert_back(T const& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_insert_front(T const& value, std::endian endian = std::endian::native) noexcept;

    constexpr bool try_read(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_read_reverse(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;

    constexpr bool try_read_back(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_read_front(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_read_back_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;
    constexpr bool try_read_front_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept;

    template <ArithmeticOrByte T> bool try_read(std::size_t const& offset, T& value, std::endian endian = std::endian::native) const noexcept;
    template <ArithmeticOrByte T> bool try_read_back(T& value, std::endian endian = std::endian::native) const noexcept;
    template <ArithmeticOrByte T> bool try_read_front(T& value, std::endian endian = std::endian::native) const noexcept;

    bool try_remove(std::size_t const& offset, std::size_t const& number_of_bytes = 1) noexcept;

    bool try_remove_back(std::size_t const& number_of_bytes = 1) noexcept;
    bool try_remove_front(std::size_t const& number_of_bytes = 1) noexcept;

    template <ArithmeticOrByte T> bool try_remove(std::size_t const& offset) noexcept;
    template <ArithmeticOrByte T> bool try_remove_back() noexcept;
    template <ArithmeticOrByte T> bool try_remove_front() noexcept;

    template <ArithmeticOrByte T> bool try_extract(std::size_t const& offset, T& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_extract_back(T& value, std::endian endian = std::endian::native) noexcept;
    template <ArithmeticOrByte T> bool try_extract_front(T& value, std::endian endian = std::endian::native) noexcept;

    void overwrite(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes);
    void overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes);

    void overwrite(std::size_t const& offset, std::byte const& byte);
    void overwrite(std::size_t const& offset, std::byte const* begin, std::byte const* end);
    void overwrite(std::size_t const& offset, std::span<std::byte> const& data);
    void overwrite_back(std::byte const& byte);
    void overwrite_back(std::byte const* begin, std::byte const* end);
    void overwrite_back(std::byte const* begin, std::size_t const& number_of_bytes);
    void overwrite_back(std::span<std::byte> const& data);
    void overwrite_front(std::byte const& byte);
    void overwrite_front(std::byte const* begin, std::byte const* end);
    void overwrite_front(std::byte const* begin, std::size_t const& number_of_bytes);
    void overwrite_front(std::span<std::byte> const& data);

    void overwrite_reverse(std::size_t const& offset, std::byte const& byte);
    void overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end);
    void overwrite_reverse(std::size_t const& offset, std::span<std::byte> const& data);
    void overwrite_back_reverse(std::byte const& byte);
    void overwrite_back_reverse(std::byte const* begin, std::byte const* end);
    void overwrite_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes);
    void overwrite_back_reverse(std::span<std::byte> const& data);
    void overwrite_front_reverse(std::byte const& byte);
    void overwrite_front_reverse(std::byte const* begin, std::byte const* end);
    void overwrite_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes);
    void overwrite_front_reverse(std::span<std::byte> const& data);

    template <ArithmeticOrByte T> void overwrite(std::size_t const& offset, T const& value, std::endian endian = std::endian::native);
    template <ArithmeticOrByte T> void overwrite_back(T const& value, std::endian endian = std::endian::native);
    template <ArithmeticOrByte T> void overwrite_front(T const& value, std::endian endian = std::endian::native);

    void insert(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes);
    void insert_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes);

    void insert(std::size_t const& offset, std::byte const& byte);
    void insert(std::size_t const& offset, std::byte const* begin, std::byte const* end);
    void insert(std::size_t const& offset, std::span<std::byte> const& data);
    void insert_back(std::byte const& byte);
    void insert_back(std::byte const* begin, std::byte const* end);
    void insert_back(std::byte const* begin, std::size_t const& number_of_bytes);
    void insert_back(std::span<std::byte> const& data);
    void insert_front(std::byte const& byte);
    void insert_front(std::byte const* begin, std::byte const* end);
    void insert_front(std::byte const* begin, std::size_t const& number_of_bytes);
    void insert_front(std::span<std::byte> const& data);

    void insert_reverse(std::size_t const& offset, std::byte const& byte);
    void insert_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end);
    void insert_reverse(std::size_t const& offset, std::span<std::byte> const& data);
    void insert_back_reverse(std::byte const& byte);
    void insert_back_reverse(std::byte const* begin, std::byte const* end);
    void insert_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes);
    void insert_back_reverse(std::span<std::byte> const& data);
    void insert_front_reverse(std::byte const& byte);
    void insert_front_reverse(std::byte const* begin, std::byte const* end);
    void insert_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes);
    void insert_front_reverse(std::span<std::byte> const& data);

    template <ArithmeticOrByte T> void insert(std::size_t const& offset, T const& value, std::endian endian = std::endian::native);
    template <ArithmeticOrByte T> void insert_back(T const& value, std::endian endian = std::endian::native);
    template <ArithmeticOrByte T> void insert_front(T const& value, std::endian endian = std::endian::native);

    void remove(std::size_t const& offset, std::size_t const& number_of_bytes = 1);
    void remove_back(std::size_t const& number_of_bytes = 1);
    void remove_front(std::size_t const& number_of_bytes = 1);

    template <ArithmeticOrByte T> [[nodiscard]] T read(std::size_t const& offset, std::endian endian = std::endian::native) const;
    template <ArithmeticOrByte T> [[nodiscard]] T read_back(std::endian endian = std::endian::native) const;
    template <ArithmeticOrByte T> [[nodiscard]] T read_front(std::endian endian = std::endian::native) const;

    template <ArithmeticOrByte T> [[nodiscard]] T extract(std::size_t const& offset, std::endian endian = std::endian::native);
    template <ArithmeticOrByte T> [[nodiscard]] T extract_back(std::endian endian = std::endian::native);
    template <ArithmeticOrByte T> [[nodiscard]] T extract_front(std::endian endian = std::endian::native);

  private:
    static std::size_t data_shift_right(std::byte* data, std::size_t const& size, std::size_t const& offset, std::size_t const& shift);
    static std::size_t data_shift_left(std::byte* data, std::size_t const& size, std::size_t const& offset, std::size_t const& shift);

    static std::size_t byte_copy(std::byte* dst, std::byte const* src, std::size_t const& size);
    static std::size_t byte_copy_reverse(std::byte* dst, std::byte const* src, std::size_t const& size);

    static void handle_overwrite_exception();
    static void handle_insert_exception();
    static void handle_remove_exception();
    static void handle_read_exception();

    std::byte*  m_data;
    std::size_t m_size;
    std::size_t m_pos_idx = 0;
  };

  template <std::size_t N>
  inline constexpr obj::obj(std::byte (&buffer)[N], std::size_t const& position_idx) noexcept
      : obj(buffer, N, position_idx)
  {
  }

  template <ArithmeticOrByte T> inline bool obj::try_overwrite(std::size_t const& offset, T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_overwrite(offset, reinterpret_cast<std::byte const*>(&value), sizeof(T));
    else
      return this->try_overwrite_reverse(offset, reinterpret_cast<std::byte const*>(&value), sizeof(T));
  }

  template <ArithmeticOrByte T> inline bool obj::try_overwrite_back(T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_overwrite_back(reinterpret_cast<std::byte const*>(&value), sizeof(T));
    else
      return this->try_overwrite_back_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(T));
  }

  template <ArithmeticOrByte T> inline bool obj::try_overwrite_front(T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_overwrite_front(reinterpret_cast<std::byte const*>(&value), sizeof(T));
    else
      return this->try_overwrite_front_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(T));
  }

  template <ArithmeticOrByte T> inline bool obj::try_insert(std::size_t const& offset, T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_insert(offset, reinterpret_cast<std::byte const*>(&value), sizeof(value));
    else
      return this->try_insert_reverse(offset, reinterpret_cast<std::byte const*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_insert_back(T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_insert_back(reinterpret_cast<std::byte const*>(&value), sizeof(value));
    else
      return this->try_insert_back_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_insert_front(T const& value, std::endian endian) noexcept
  {
    if (endian == std::endian::native)
      return this->try_insert_front(reinterpret_cast<std::byte const*>(&value), sizeof(value));
    else
      return this->try_insert_front_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_read(std::size_t const& offset, T& value, std::endian endian) const noexcept
  {
    if (endian == std::endian::native)
    {
      return this->try_read(offset, reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
    else
    {
      return this->try_read_reverse(offset, reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
  }

  template <ArithmeticOrByte T> inline bool obj::try_read_back(T& value, std::endian endian) const noexcept
  {
    if (endian == std::endian::native)
    {
      return this->try_read_back(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
    else
    {
      return this->try_read_back_reverse(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    }
  }

  template <ArithmeticOrByte T> inline bool obj::try_read_front(T& value, std::endian endian) const noexcept
  {
    if (endian == std::endian::native)
      return this->try_read_front(reinterpret_cast<std ::byte*>(&value), sizeof(value));
    else
      return this->try_read_front_reverse(reinterpret_cast<std ::byte*>(&value), sizeof(value));
  }

  template <ArithmeticOrByte T> inline bool obj::try_remove(std::size_t const& offset) noexcept { return this->try_remove(offset, sizeof(T)); }

  template <ArithmeticOrByte T> inline bool obj::try_remove_back() noexcept { return this->try_remove_back(sizeof(T)); }

  template <ArithmeticOrByte T> inline bool obj::try_remove_front() noexcept { return this->try_remove_front(sizeof(T)); }

  template <ArithmeticOrByte T> inline bool obj::try_extract(std::size_t const& offset, T& value, std::endian endian) noexcept
  {
    return this->try_read(offset, value, endian) && this->try_remove<T>(offset);
  }

  template <ArithmeticOrByte T> inline bool obj::try_extract_back(T& value, std::endian endian) noexcept
  {
    return this->try_read_back(value, endian) && this->try_remove_back<T>();
  }

  template <ArithmeticOrByte T> inline bool obj::try_extract_front(T& value, std::endian endian) noexcept
  {
    return this->try_read_front(value, endian) && this->try_remove_front<T>();
  }

  template <ArithmeticOrByte T> inline void obj::overwrite(std::size_t const& offset, T const& value, std::endian endian)
  {
    if (endian == std::endian::native)
      return this->overwrite(offset, reinterpret_cast<std::byte const*>(&value), sizeof(T));
    else
      return this->overwrite_reverse(offset, reinterpret_cast<std::byte const*>(&value), sizeof(T));
  }

  template <ArithmeticOrByte T> inline void obj::overwrite_back(T const& value, std::endian endian)
  {
    if (endian == std::endian::native)
      return this->overwrite_back(reinterpret_cast<std::byte const*>(&value), sizeof(T));
    else
      return this->overwrite_back_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(T));
  }

  template <ArithmeticOrByte T> inline void obj::overwrite_front(T const& value, std::endian endian)
  {
    if (endian == std::endian::native)
      return this->overwrite_front(reinterpret_cast<std::byte const*>(&value), sizeof(T));
    else
      return this->overwrite_front_reverse(reinterpret_cast<std::byte const*>(&value), sizeof(T));
  }

  template <ArithmeticOrByte T> inline void obj::insert(std::size_t const& offset, T const& value, std::endian endian)
  {
    if (!this->try_insert(offset, value, endian))
      return obj::handle_insert_exception();
  }

  template <ArithmeticOrByte T> inline void obj::insert_back(T const& value, std::endian endian)
  {
    if (!this->try_insert_back(value, endian))
      return obj::handle_insert_exception();
  }

  template <ArithmeticOrByte T> inline void obj::insert_front(T const& value, std::endian endian)
  {
    if (!this->try_insert_front(value, endian))
      return obj::handle_insert_exception();
  }

  template <ArithmeticOrByte T> inline T obj::read(std::size_t const& offset, std::endian endian) const
  {
    T ret{};
    if (!this->try_read(offset, ret, endian))
      obj::handle_read_exception();

    return ret;
  }

  template <ArithmeticOrByte T> inline T obj::read_back(std::endian endian) const
  {
    T ret{};
    if (!this->try_read_back(ret, endian))
      obj::handle_read_exception();

    return ret;
  }

  template <ArithmeticOrByte T> inline T obj::read_front(std::endian endian) const
  {
    T ret{};
    if (!this->try_read_front(ret, endian))
      obj::handle_read_exception();

    return ret;
  }

  template <ArithmeticOrByte T> inline T obj::extract(std::size_t const& offset, std::endian endian)
  {
    T ret = this->read<T>(offset, endian);
    this->remove(offset, sizeof(T));
    return ret;
  }

  template <ArithmeticOrByte T> inline T obj::extract_back(std::endian endian)
  {
    T ret = this->read_back<T>(endian);
    this->remove_back(sizeof(T));
    return ret;
  }

  template <ArithmeticOrByte T> inline T obj::extract_front(std::endian endian)
  {
    T ret = this->read_front<T>(endian);
    this->remove_front(sizeof(T));
    return ret;
  }

  inline constexpr obj::obj(std::byte* begin, std::byte* end) noexcept
      : obj(begin, end - begin, 0)
  {
  }
  inline constexpr obj::obj(std::byte* begin, std::byte* end, std::byte* position) noexcept
      : obj(begin, end - begin, position - begin)
  {
  }
  inline constexpr obj::obj(std::byte* begin, std::size_t const& size, std::size_t const& position_idx) noexcept
      : m_data(begin)
      , m_size(size)
      , m_pos_idx(position_idx)
  {
  }
  inline constexpr std::size_t          obj::get_total_number_of_bytes() const noexcept { return this->m_size; }
  inline constexpr std::size_t          obj::get_number_of_free_bytes() const noexcept { return this->m_size - this->m_pos_idx; }
  inline constexpr std::size_t          obj::get_number_of_used_bytes() const noexcept { return this->m_pos_idx; }
  inline constexpr std::span<std::byte> obj::get_blob() const noexcept { return std::span<std::byte>(this->m_data, this->m_pos_idx); }
  inline constexpr void                 obj::clear() noexcept { this->m_pos_idx = 0; }
  inline constexpr bool                 obj::try_adjust_position(std::ptrdiff_t const& offset) noexcept
  {
    if ((offset > 0) && (this->m_pos_idx + offset) > this->m_size)
      return false;
    if ((offset < 0) && (this->m_pos_idx < -offset))
      return false;

    this->m_pos_idx += offset;
    return true;
  }
  inline constexpr bool obj::try_set_position(std::size_t const& position) noexcept
  {
    if (this->m_size < position)
      return false;
    this->m_pos_idx = position;
    return true;
  }
  inline bool obj::try_overwrite(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    std::size_t const end_idx = offset + number_of_bytes;
    if (this->m_pos_idx < end_idx)
      return false;
    obj::byte_copy(&this->m_data[offset], begin, number_of_bytes);
    return true;
  }
  inline bool obj::try_overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    std::size_t const end_idx = offset + number_of_bytes;
    if (this->m_pos_idx < end_idx)
      return false;
    obj::byte_copy_reverse(&this->m_data[offset], begin, number_of_bytes);
    return true;
  }
  inline bool obj::try_overwrite(std::size_t const& offset, std::byte const& byte) noexcept { return this->try_overwrite(offset, &byte, 1); }
  inline bool obj::try_overwrite(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_overwrite(offset, begin, end - begin);
  }
  inline bool obj::try_overwrite(std::size_t const& offset, std::span<std::byte> const& data) noexcept
  {
    return this->try_overwrite(offset, data.data(), data.size_bytes());
  }
  inline bool obj::try_overwrite_back(std::byte const& byte) noexcept { return this->try_overwrite(this->m_pos_idx - 1, byte); }
  inline bool obj::try_overwrite_back(std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_overwrite(this->m_pos_idx - (end - begin), begin, end);
  }
  inline bool obj::try_overwrite_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_overwrite(this->m_pos_idx - number_of_bytes, begin, number_of_bytes);
  }
  inline bool obj::try_overwrite_back(std::span<std::byte> const& data) noexcept { return this->try_overwrite(this->m_pos_idx - data.size_bytes(), data); }
  inline bool obj::try_overwrite_front(std::byte const& byte) noexcept { return this->try_overwrite(0, byte); }
  inline bool obj::try_overwrite_front(std::byte const* begin, std::byte const* end) noexcept { return this->try_overwrite(0, begin, end); }
  inline bool obj::try_overwrite_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_overwrite(0, begin, number_of_bytes);
  }
  inline bool obj::try_overwrite_front(std::span<std::byte> const& data) noexcept { return this->try_overwrite(0, data); }
  inline bool obj::try_overwrite_reverse(std::size_t const& offset, std::byte const& byte) noexcept { return this->try_overwrite_reverse(offset, &byte, 1); }
  inline bool obj::try_overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_overwrite_reverse(offset, begin, end - begin);
  }
  inline bool obj::try_overwrite_reverse(std::size_t const& offset, std::span<std::byte> const& data) noexcept
  {
    return this->try_overwrite_reverse(offset, data.data(), data.size_bytes());
  }
  inline bool obj::try_overwrite_back_reverse(std::byte const& byte) noexcept { return this->try_overwrite_reverse(this->m_pos_idx - 1, &byte, 1); }
  inline bool obj::try_overwrite_back_reverse(std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_overwrite_reverse(this->m_pos_idx - (end - begin), begin, end);
  }
  inline bool obj::try_overwrite_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_overwrite_reverse(this->m_pos_idx - number_of_bytes, begin, number_of_bytes);
  }
  inline bool obj::try_overwrite_back_reverse(std::span<std::byte> const& data) noexcept
  {
    return this->try_overwrite_reverse(this->m_pos_idx - data.size_bytes(), data);
  }
  inline bool obj::try_overwrite_front_reverse(std::byte const& byte) noexcept { return this->try_overwrite_reverse(0, byte); }
  inline bool obj::try_overwrite_front_reverse(std::byte const* begin, std::byte const* end) noexcept { return this->try_overwrite_reverse(0, begin, end); }
  inline bool obj::try_overwrite_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_overwrite_reverse(0, begin, number_of_bytes);
  }
  inline bool obj::try_overwrite_front_reverse(std::span<std::byte> const& data) noexcept { return this->try_overwrite_reverse(0, data); }
  inline bool obj::try_insert(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    if (this->m_pos_idx < offset)
      return false;

    std::size_t const end_idx = this->m_pos_idx + number_of_bytes;
    if (this->m_size < end_idx)
      return false;

    std::size_t const tmp = obj::data_shift_right(this->m_data, this->m_pos_idx, offset, number_of_bytes);
    obj::byte_copy(&this->m_data[offset], begin, number_of_bytes);
    this->m_pos_idx += tmp;
    return true;
  }
  inline bool obj::try_insert_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    if (this->m_pos_idx < offset)
      return false;

    std::size_t const end_idx = this->m_pos_idx + number_of_bytes;
    if (this->m_size < end_idx)
      return false;

    std::size_t const tmp = obj::data_shift_right(this->m_data, this->m_pos_idx, offset, number_of_bytes);
    obj::byte_copy_reverse(&this->m_data[offset], begin, number_of_bytes);
    this->m_pos_idx += tmp;
    return true;
  }
  inline bool obj::try_insert(std::size_t const& offset, std::byte const& byte) noexcept { return this->try_insert(offset, &byte, 1); }
  inline bool obj::try_insert(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_insert(offset, begin, end - begin);
  }
  inline bool obj::try_insert(std::size_t const& offset, std::span<std::byte> const& data) noexcept
  {
    return this->try_insert(offset, data.data(), data.size_bytes());
  }
  inline bool obj::try_insert_back(std::byte const& byte) noexcept { return this->try_insert_back(&byte, 1); }
  inline bool obj::try_insert_back(std::byte const* begin, std::byte const* end) noexcept { return this->try_insert_back(begin, end - begin); }
  inline bool obj::try_insert_back(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_insert(this->m_pos_idx, begin, number_of_bytes);
  }
  inline bool obj::try_insert_back(std::span<std::byte> const& data) noexcept { return this->try_insert_back(data.data(), data.size_bytes()); }
  inline bool obj::try_insert_front(std::byte const& byte) noexcept { return this->try_insert_front(&byte, 1); }
  inline bool obj::try_insert_front(std::byte const* begin, std::byte const* end) noexcept { return this->try_insert_front(begin, end - begin); }
  inline bool obj::try_insert_front(std::byte const* begin, std::size_t const& number_of_bytes) noexcept { return this->try_insert(0, begin, number_of_bytes); }
  inline bool obj::try_insert_front(std::span<std::byte> const& data) noexcept { return this->try_insert_front(data.data(), data.size_bytes()); }
  inline bool obj::try_insert_reverse(std::size_t const& offset, std::byte const& byte) noexcept { return this->try_insert_reverse(offset, &byte, 1); }
  inline bool obj::try_insert_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_insert_reverse(offset, begin, end - begin);
  }
  inline bool obj::try_insert_reverse(std::size_t const& offset, std::span<std::byte> const& data) noexcept
  {
    return this->try_insert_reverse(offset, data.data(), data.size_bytes());
  }
  inline bool obj::try_insert_back_reverse(std::byte const& byte) noexcept { return this->try_insert_back_reverse(&byte, 1); }
  inline bool obj::try_insert_back_reverse(std::byte const* begin, std::byte const* end) noexcept { return this->try_insert_back_reverse(begin, end - begin); }
  inline bool obj::try_insert_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_insert_reverse(this->m_pos_idx, begin, number_of_bytes);
  }
  inline bool obj::try_insert_back_reverse(std::span<std::byte> const& data) noexcept { return this->try_insert_back_reverse(data.data(), data.size_bytes()); }
  inline bool obj::try_insert_front_reverse(std::byte const& byte) noexcept { return this->try_insert_front_reverse(&byte, 1); }
  inline bool obj::try_insert_front_reverse(std::byte const* begin, std::byte const* end) noexcept
  {
    return this->try_insert_front_reverse(begin, end - begin);
  }
  inline bool obj::try_insert_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) noexcept
  {
    return this->try_insert_reverse(0, begin, number_of_bytes);
  }
  inline bool obj::try_insert_front_reverse(std::span<std::byte> const& data) noexcept
  {
    return this->try_insert_front_reverse(data.data(), data.size_bytes());
  }
  inline constexpr bool obj::try_read(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    if (this->m_pos_idx < (offset + number_of_bytes))
      return false;

    obj::byte_copy(ptr, &this->m_data[offset], number_of_bytes);
    return true;
  }
  inline constexpr bool obj::try_read_reverse(std::size_t const& offset, std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    if (this->m_pos_idx < (offset + number_of_bytes))
      return false;

    obj::byte_copy_reverse(ptr, &this->m_data[offset], number_of_bytes);
    return true;
  }
  inline constexpr bool obj::try_read_back(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_read(this->m_pos_idx - number_of_bytes, ptr, number_of_bytes);
  }
  inline constexpr bool obj::try_read_front(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_read(0, ptr, number_of_bytes);
  }
  inline constexpr bool obj::try_read_back_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_read_reverse(this->m_pos_idx - number_of_bytes, ptr, number_of_bytes);
  }
  inline constexpr bool obj::try_read_front_reverse(std::byte* ptr, std::size_t const& number_of_bytes) const noexcept
  {
    return this->try_read_reverse(0, ptr, number_of_bytes);
  }
  inline bool obj::try_remove(std::size_t const& offset, std::size_t const& number_of_bytes) noexcept
  {
    if (this->m_pos_idx < (offset + number_of_bytes))
      return false;

    this->m_pos_idx -= this->data_shift_left(this->m_data, this->m_pos_idx, offset, number_of_bytes);
    return true;
  }
  inline bool obj::try_remove_back(std::size_t const& number_of_bytes) noexcept { return this->try_remove(this->m_pos_idx - number_of_bytes, number_of_bytes); }
  inline bool obj::try_remove_front(std::size_t const& number_of_bytes) noexcept { return this->try_remove(0, number_of_bytes); }
  inline void obj::overwrite(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_overwrite(offset, begin, number_of_bytes))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_overwrite_reverse(offset, begin, number_of_bytes))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite(std::size_t const& offset, std::byte const& byte)
  {
    if (!this->try_overwrite(offset, byte))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite(std::size_t const& offset, std::byte const* begin, std::byte const* end)
  {
    if (!this->try_overwrite(offset, begin, end))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite(std::size_t const& offset, std::span<std::byte> const& data)
  {
    if (!this->try_overwrite(offset, data))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back(std::byte const& byte)
  {
    if (!this->try_overwrite_back(byte))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back(std::byte const* begin, std::byte const* end)
  {
    if (!this->try_overwrite_back(begin, end))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_overwrite_back(begin, number_of_bytes))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back(std::span<std::byte> const& data)
  {
    if (!this->try_overwrite_back(data))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front(std::byte const& byte)
  {
    if (!this->try_overwrite_front(byte))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front(std::byte const* begin, std::byte const* end)
  {
    if (!this->try_overwrite_front(begin, end))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_overwrite_front(begin, number_of_bytes))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front(std::span<std::byte> const& data)
  {
    if (!this->try_overwrite_front(data))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_reverse(std::size_t const& offset, std::byte const& byte)
  {
    if (!this->try_overwrite_reverse(offset, byte))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end)
  {
    if (!this->try_overwrite_reverse(offset, begin, end))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_reverse(std::size_t const& offset, std::span<std::byte> const& data)
  {
    if (!this->try_overwrite_reverse(offset, data))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back_reverse(std::byte const& byte)
  {
    if (!this->try_overwrite_back_reverse(byte))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back_reverse(std::byte const* begin, std::byte const* end)
  {
    if (!this->try_overwrite_back_reverse(begin, end))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_overwrite_back_reverse(begin, number_of_bytes))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_back_reverse(std::span<std::byte> const& data)
  {
    if (!this->try_overwrite_back_reverse(data))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front_reverse(std::byte const& byte)
  {
    if (!this->try_overwrite_front_reverse(byte))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front_reverse(std::byte const* begin, std::byte const* end)
  {
    if (!this->try_overwrite_front_reverse(begin, end))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_overwrite_front_reverse(begin, number_of_bytes))
      return obj::handle_overwrite_exception();
  }
  inline void obj::overwrite_front_reverse(std::span<std::byte> const& data)
  {
    if (!this->try_overwrite_front_reverse(data))
      return obj::handle_overwrite_exception();
  }
  inline void obj::insert(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_insert(offset, begin, number_of_bytes))
      return obj::handle_insert_exception();
  }
  inline void obj::insert_reverse(std::size_t const& offset, std::byte const* begin, std::size_t const& number_of_bytes)
  {
    if (!this->try_insert_reverse(offset, begin, number_of_bytes))
      return obj::handle_insert_exception();
  }
  inline void obj::insert(std::size_t const& offset, std::byte const& byte) { return this->insert(offset, &byte, 1); }
  inline void obj::insert(std::size_t const& offset, std::byte const* begin, std::byte const* end) { return this->insert(offset, begin, end - begin); }
  inline void obj::insert(std::size_t const& offset, std::span<std::byte> const& data) { return this->insert(offset, data.data(), data.size_bytes()); }
  inline void obj::insert_back(std::byte const& byte) { return this->insert(this->m_pos_idx, byte); }
  inline void obj::insert_back(std::byte const* begin, std::byte const* end) { return this->insert(this->m_pos_idx, begin, end); }
  inline void obj::insert_back(std::byte const* begin, std::size_t const& number_of_bytes) { return this->insert(this->m_pos_idx, begin, number_of_bytes); }
  inline void obj::insert_back(std::span<std::byte> const& data) { return this->insert(this->m_pos_idx, data); }
  inline void obj::insert_front(std::byte const& byte) { return this->insert(0, byte); }
  inline void obj::insert_front(std::byte const* begin, std::byte const* end) { return this->insert(0, begin, end); }
  inline void obj::insert_front(std::byte const* begin, std::size_t const& number_of_bytes) { return this->insert(0, begin, number_of_bytes); }
  inline void obj::insert_front(std::span<std::byte> const& data) { return this->insert(0, data); }
  inline void obj::insert_reverse(std::size_t const& offset, std::byte const& byte) { return this->insert_reverse(offset, &byte, 1); }
  inline void obj::insert_reverse(std::size_t const& offset, std::byte const* begin, std::byte const* end)
  {
    return this->insert_reverse(offset, begin, end - begin);
  }
  inline void obj::insert_reverse(std::size_t const& offset, std::span<std::byte> const& data)
  {
    return this->insert_reverse(offset, data.data(), data.size_bytes());
  }
  inline void obj::insert_back_reverse(std::byte const& byte) { return this->insert_reverse(this->m_pos_idx, byte); }
  inline void obj::insert_back_reverse(std::byte const* begin, std::byte const* end) { return this->insert_reverse(this->m_pos_idx, begin, end); }
  inline void obj::insert_back_reverse(std::byte const* begin, std::size_t const& number_of_bytes)
  {
    return this->insert_reverse(this->m_pos_idx, begin, number_of_bytes);
  }
  inline void obj::insert_back_reverse(std::span<std::byte> const& data) { return this->insert_reverse(this->m_pos_idx, data); }
  inline void obj::insert_front_reverse(std::byte const& byte) { return this->insert_reverse(0, byte); }
  inline void obj::insert_front_reverse(std::byte const* begin, std::byte const* end) { return this->insert_reverse(0, begin, end); }
  inline void obj::insert_front_reverse(std::byte const* begin, std::size_t const& number_of_bytes) { return this->insert_reverse(0, begin, number_of_bytes); }
  inline void obj::insert_front_reverse(std::span<std::byte> const& data) { return this->insert_reverse(0, data); }
  inline void obj::remove(std::size_t const& offset, std::size_t const& number_of_bytes)
  {
    if (!this->try_remove(offset, number_of_bytes))
      return obj::handle_remove_exception();
  }
  inline void        obj::remove_back(std::size_t const& number_of_bytes) { return this->remove(this->m_pos_idx - number_of_bytes, number_of_bytes); }
  inline void        obj::remove_front(std::size_t const& number_of_bytes) { return this->remove(0, number_of_bytes); }
  inline std::size_t obj::data_shift_right(std::byte* data, std::size_t const& size, std::size_t const& offset, std::size_t const& shift)
  {
    for (std::size_t i = size + shift; i > (offset + shift);)
    {
      --i;
      data[i] = data[i - shift];
    }
    return shift;
  }
  inline std::size_t obj::data_shift_left(std::byte* data, std::size_t const& size, std::size_t const& offset, std::size_t const& shift)
  {
    for (std::size_t i = offset; i < size - shift; i++)
    {
      data[i] = data[i + shift];
    }
    return shift;
  }
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
}    // namespace wlib::blob

#endif    // !WLIB_CRC_INTERFACE_HPP
