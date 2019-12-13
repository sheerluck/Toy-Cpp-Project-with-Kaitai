cmake_minimum_required(VERSION 3.16)
project(mkv)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-march=native -mtune=native -O3 -mmmx -msse -msse2 -msse3 -pedantic -Wextra -Wshadow -Wnon-virtual-dtor -Wdelete-non-virtual-dtor -fgraphite-identity -floop-nest-optimize -fdevirtualize-at-ltrans -fipa-pta -fno-semantic-interposition -flto=9 -fuse-linker-plugin -pipe -falign-functions=32")

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(fmt REQUIRED)

add_definitions(-DKS_STR_ENCODING_NONE)

include_directories(.)

add_executable(mkv main.cpp
        utils.h utils.cpp
        calmsize.h calmsize.cpp

        ksy_helper.h ksy_helper.cpp
        ksy/mkv.h ksy/mkv.cpp
        ksy/mp4.h ksy/mp4.cpp
        ksy/mp4_atom.h ksy/mp4_atom.cpp
        kaitai/kaitaistream.cpp)

target_link_libraries(mkv fmt::fmt)
