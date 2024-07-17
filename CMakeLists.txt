cmake_minimum_required(VERSION 3.19)



project(WLib-Project
 VERSION 0.0.0.0
 DESCRIPTION "A dummy Project"
 HOMEPAGE_URL ""
 LANGUAGES C CXX ASM
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

message(STATUS "########################|")
message(STATUS "#          W-Lib-Project:${CMAKE_PROJECT_NAME}")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/externals")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/w-lib")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tst")

