cmake_minimum_required(VERSION 3.12)
project(cxx-tasks VERSION 0.2.0 LANGUAGES CXX DESCRIPTION "Home tasks for C++ training")

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

include(CTest)

find_package(Catch2 2.8 REQUIRED)
include(Catch)
add_library(catch_entry test_entry.cpp)
target_link_libraries(catch_entry PUBLIC Catch2::Catch2)

set(BUILD_SHARED_LIBS ON) # need for Boost::system
find_package(Boost 1.67 REQUIRED COMPONENTS system)

add_subdirectory(iomanip)
add_subdirectory(proxy)
add_subdirectory(iterator)
add_subdirectory(variant)
#add_subdirectory(type_map)
add_subdirectory(csv_parser)
add_subdirectory(json_parser)
#add_subdirectory(strided_range)

find_program(AWK_EXECUTABLE awk gawk DOC "awk executable")
file(GLOB_RECURSE SRCS *.hpp)
add_custom_target(encrypt COMMAND ${AWK_EXECUTABLE} -i inplace -v enc=1 -f ${CMAKE_SOURCE_DIR}/encrypt.awk ${SRCS})
add_custom_target(decrypt COMMAND ${AWK_EXECUTABLE} -i inplace -v enc=0 -f ${CMAKE_SOURCE_DIR}/encrypt.awk ${SRCS})

add_custom_target(answer COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${CMAKE_SOURCE_DIR} -P ${CMAKE_SOURCE_DIR}/find_answers.cmake)
