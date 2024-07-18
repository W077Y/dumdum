#include <iostream>
#include <ut_catch.hpp>
#include <wlib_BLOB.hpp>

void print_buffer(wlib::blob::MemoryBlob const& blob, std::span<std::byte> const& buffer)
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
  std::byte            buffer[30]{};
  std::byte*           buffer_begin = buffer;
  std::byte*           buffer_end   = buffer + sizeof(buffer);
  std::span<std::byte> buffer_span{ buffer };
  {
    wlib::blob::MemoryBlob blob{ buffer_begin, buffer_end };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 30);
    REQUIRE(blob.get_number_of_used_bytes() == 0);
  }
  {
    wlib::blob::MemoryBlob blob{ buffer_begin, sizeof(buffer) };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 30);
    REQUIRE(blob.get_number_of_used_bytes() == 0);
  }
  {
    wlib::blob::MemoryBlob blob{ buffer };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 30);
    REQUIRE(blob.get_number_of_used_bytes() == 0);
  }
  {
    wlib::blob::MemoryBlob blob{ buffer_span };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 30);
    REQUIRE(blob.get_number_of_used_bytes() == 0);
  }
  {
    wlib::blob::MemoryBlob blob{ buffer_begin, buffer_end, buffer_begin + 3 };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 27);
    REQUIRE(blob.get_number_of_used_bytes() == 3);
  }
  {
    wlib::blob::MemoryBlob blob{ buffer_begin, sizeof(buffer), 3 };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 27);
    REQUIRE(blob.get_number_of_used_bytes() == 3);
  }
  {
    wlib::blob::MemoryBlob blob{ buffer_span, 3 };
    REQUIRE(blob.get_total_number_of_bytes() == 30);
    REQUIRE(blob.get_number_of_free_bytes() == 27);
    REQUIRE(blob.get_number_of_used_bytes() == 3);
  }
}

TEST_CASE()
{
  std::byte buffer[30]{};

  wlib::blob::MemoryBlob blob{ buffer };

  REQUIRE(blob.get_total_number_of_bytes() == 30);
  REQUIRE(blob.get_number_of_free_bytes() == 30);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  blob.insert_back(static_cast<std::byte>(0x03));
  blob.insert_back(static_cast<std::byte>(0x04));
  blob.insert_front(static_cast<std::byte>(0x02));
  blob.insert_front(static_cast<std::byte>(0x01));

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
  std::byte buffer[14]{};

  wlib::blob::MemoryBlob blob{ buffer };

  REQUIRE(blob.get_total_number_of_bytes() == 14);
  REQUIRE(blob.get_number_of_free_bytes() == 14);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  uint32_t val_in[] = {
    0x0011'2233,
    0x4455'6677,
    0x8899'AABB,
    0xCCDD'EEFF,
  };

  std::size_t suc_count = 0;
  for (uint32_t val : val_in)
  {
    if (blob.try_insert_back(val))
      suc_count++;
  }
  REQUIRE(suc_count == 3);
  REQUIRE(blob.get_total_number_of_bytes() == 14);
  REQUIRE(blob.get_number_of_free_bytes() == 2);
  REQUIRE(blob.get_number_of_used_bytes() == 12);

  uint32_t val_out[4] = {};

  suc_count = 0;
  for (uint32_t& val : val_out)
  {
    if (blob.try_extract_front(val))
      suc_count++;
  }
  REQUIRE(suc_count == 3);
  for (std::size_t i = 0; i < suc_count; i++)
  {
    REQUIRE(val_in[i] == val_out[i]);
  }

  blob.clear();
  REQUIRE(blob.get_total_number_of_bytes() == 14);
  REQUIRE(blob.get_number_of_free_bytes() == 14);
  REQUIRE(blob.get_number_of_used_bytes() == 0);
}

TEST_CASE()
{
  static constexpr std::size_t buffer_size = 1 + sizeof(std::byte) + sizeof(char) + sizeof(signed char) + sizeof(unsigned char) + sizeof(char8_t) +
                                             sizeof(char16_t) + sizeof(char32_t) + sizeof(signed short) + sizeof(unsigned short) + sizeof(signed int) +
                                             sizeof(unsigned int) + sizeof(signed long) + sizeof(unsigned long) + sizeof(signed long long) +
                                             sizeof(unsigned long long) + sizeof(float) + sizeof(double) + sizeof(long double);

  std::byte buffer[buffer_size]{};

  wlib::blob::MemoryBlob blob{ buffer };

  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  bool ret = true;
  ret &= blob.try_insert_back(static_cast<std::byte>(0x01));
  ret &= blob.try_insert_back(static_cast<char>(0x02));
  ret &= blob.try_insert_back(static_cast<signed char>(0x03));
  ret &= blob.try_insert_back(static_cast<unsigned char>(0x04));
  ret &= blob.try_insert_back(static_cast<char8_t>(0x05));
  ret &= blob.try_insert_back(static_cast<char16_t>(0x06));
  ret &= blob.try_insert_back(static_cast<char32_t>(0x07));
  ret &= blob.try_insert_back(static_cast<signed short>(0x08));
  ret &= blob.try_insert_back(static_cast<unsigned short>(0x09));
  ret &= blob.try_insert_back(static_cast<signed int>(0x0A));
  ret &= blob.try_insert_back(static_cast<unsigned int>(0x0B));
  ret &= blob.try_insert_back(static_cast<signed long>(0x0C));
  ret &= blob.try_insert_back(static_cast<unsigned long>(0x0D));
  ret &= blob.try_insert_back(static_cast<signed long long>(0x0E));
  ret &= blob.try_insert_back(static_cast<unsigned long long>(0x0F));
  ret &= blob.try_insert_back(static_cast<float>(0x10));
  ret &= blob.try_insert_back(static_cast<double>(0x11));
  ret &= blob.try_insert_back(static_cast<long double>(0x12));

  REQUIRE(ret);
  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == 1);
  REQUIRE(blob.get_number_of_used_bytes() == buffer_size - 1);
  REQUIRE_FALSE(blob.try_insert_back(static_cast<long double>(0x13)));

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

  ret &= blob.try_extract_back(val_long_double);
  ret &= blob.try_extract_back(val_double);
  ret &= blob.try_extract_back(val_float);
  ret &= blob.try_extract_back(val_unsigned_long_long);
  ret &= blob.try_extract_back(val_signed_long_long);
  ret &= blob.try_extract_back(val_unsigned_long);
  ret &= blob.try_extract_back(val_signed_long);
  ret &= blob.try_extract_back(val_unsigned_int);
  ret &= blob.try_extract_back(val_signed_int);
  ret &= blob.try_extract_back(val_unsigned_short);
  ret &= blob.try_extract_back(val_signed_short);
  ret &= blob.try_extract_back(val_char32_t);
  ret &= blob.try_extract_back(val_char16_t);
  ret &= blob.try_extract_back(val_char8_t);
  ret &= blob.try_extract_back(val_unsigned_char);
  ret &= blob.try_extract_back(val_signed_char);
  ret &= blob.try_extract_back(val_char);
  ret &= blob.try_extract_back(val_byte);

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

  REQUIRE(blob.try_insert_back(static_cast<long long>(0x13)));

  REQUIRE(blob.get_total_number_of_bytes() == buffer_size);
  REQUIRE(blob.get_number_of_free_bytes() == buffer_size - sizeof(long long));
  REQUIRE(blob.get_number_of_used_bytes() == sizeof(long long));
}

TEST_CASE()
{
  std::byte buffer[14]{};

  wlib::blob::MemoryBlob blob{ buffer };

  REQUIRE(blob.get_total_number_of_bytes() == 14);
  REQUIRE(blob.get_number_of_free_bytes() == 14);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  REQUIRE_FALSE(blob.try_adjust_position(1000));

  REQUIRE(blob.get_number_of_free_bytes() == 14);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  REQUIRE_FALSE(blob.try_adjust_position(-1000));

  REQUIRE(blob.get_number_of_free_bytes() == 14);
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  REQUIRE(blob.try_adjust_position(5));

  REQUIRE(blob.get_number_of_free_bytes() == 9);
  REQUIRE(blob.get_number_of_used_bytes() == 5);

  REQUIRE(blob.try_adjust_position(-3));

  REQUIRE(blob.get_number_of_free_bytes() == 12);
  REQUIRE(blob.get_number_of_used_bytes() == 2);
}

TEST_CASE()
{
  std::byte buffer[14]{};

  wlib::blob::MemoryBlob blob{ buffer };

  REQUIRE(blob.get_number_of_used_bytes() == 0);
  REQUIRE_THROWS(blob.insert(1, static_cast<uint16_t>(0), std::endian::big));
  REQUIRE(blob.get_number_of_used_bytes() == 0);

  blob.insert_back(static_cast<uint32_t>(0x00AA'BBEF), std::endian::big);
  blob.insert_front(static_cast<uint32_t>(0xDECC'DDAD), std::endian::big);
  blob.insert(4, static_cast<uint16_t>(0xBE00), std::endian::big);
  REQUIRE(blob.get_number_of_used_bytes() == 10);

  REQUIRE(blob.extract<uint16_t>(1, std::endian::little) == 0xDDCC);
  REQUIRE(blob.extract<uint32_t>(3, std::endian::big) == 0x0000'AABB);
  REQUIRE(blob.extract_front<uint32_t>(std::endian::big) == 0xDEADBEEF);
  REQUIRE(blob.get_number_of_used_bytes() == 0);
}

TEST_CASE()
{
  std::byte buffer[14]{};

  wlib::blob::MemoryBlob blob{ buffer };

  REQUIRE(blob.get_number_of_used_bytes() == 0);
  REQUIRE_THROWS(blob.overwrite(0, static_cast<uint16_t>(0), std::endian::big));
  REQUIRE(blob.get_number_of_used_bytes() == 0);
  REQUIRE(blob.try_set_position(10));
  REQUIRE(blob.get_number_of_used_bytes() == 10);

  blob.overwrite_back(static_cast<uint32_t>(0x00AA'BBEF), std::endian::big);
  blob.overwrite_front(static_cast<uint32_t>(0xDECC'DDAD), std::endian::big);
  blob.overwrite(4, static_cast<uint16_t>(0xBE00), std::endian::big);
  REQUIRE(blob.get_number_of_used_bytes() == 10);

  REQUIRE(blob.extract<uint16_t>(1, std::endian::little) == 0xDDCC);
  REQUIRE(blob.extract<uint32_t>(3, std::endian::big) == 0x0000'AABB);
  REQUIRE(blob.extract_front<uint32_t>(std::endian::big) == 0xDEADBEEF);
  REQUIRE(blob.get_number_of_used_bytes() == 0);
}
