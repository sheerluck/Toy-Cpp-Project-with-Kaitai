cmake_minimum_required(VERSION 3.15)
project(Kaitai_for_Michael)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

add_executable(Kaitai_for_Michael main.cpp)
target_link_libraries(Kaitai_for_Michael fmt::fmt)
