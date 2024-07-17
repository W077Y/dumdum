cmake_minimum_required (VERSION 3.19)

message(STATUS "########################|")
set(TEST_MAIN_CPP "${CMAKE_CURRENT_LIST_DIR}/tst_main/tst_main.cpp" CACHE INTERNAL "path to tst_main.cpp")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tst_CRC")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tst_BLOB")

