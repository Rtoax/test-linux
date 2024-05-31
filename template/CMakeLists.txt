CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)

PROJECT(PROG_NAME)
execute_process(COMMAND uname -r OUTPUT_VARIABLE KERNEL_VERSION)
message(STATUS "Kernel: ${KERNEL_VERSION}")

include_directories(./)
add_subdirectory(SUBDIR)

find_library(ELF elf /usr/lib64)
find_library(RT rt /usr/lib64)
find_library(LZMA lzma /usr/lib64)

link_libraries(${ELF} ${RT} ${LZMA})

add_definitions(-MD -Wall -g -ggdb -O0 -D_GNU_SOURCE -Wuninitialized -Wreturn-type -pg)
add_definitions(-D_MAIN_USER=1)

add_executable(main.user main.user.c)
