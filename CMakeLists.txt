cmake_minimum_required(VERSION 3.15)
project(mkv)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

add_definitions(-DKS_STR_ENCODING_NONE)

include_directories(.)

add_executable(mkv main.cpp
        utils.h utils.cpp
        calmsize.h calmsize.cpp
        generated.h generated.cpp
        kaitai/kaitaistream.cpp)

target_link_libraries(mkv fmt::fmt)
