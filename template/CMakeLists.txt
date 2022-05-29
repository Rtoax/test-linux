CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

PROJECT(libcareplus)

include_directories(src)

find_library(ELF elf /usr/lib64)
find_library(RT rt /usr/lib64)
find_library(LZMA lzma /usr/lib64)

link_libraries(${ELF} ${RT} ${LZMA})

add_definitions(-MD -Wall -g -ggdb -O0 -D_GNU_SOURCE -Wuninitialized -Wreturn-type -pg)

add_executable(a.out a.c)
