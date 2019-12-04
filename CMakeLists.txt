cmake_minimum_required(VERSION 3.15)
project(mkv)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

add_executable(mkv main.cpp
        utils.h utils.cpp
        calmsize.h calmsize.cpp)
target_link_libraries(mkv fmt::fmt)
