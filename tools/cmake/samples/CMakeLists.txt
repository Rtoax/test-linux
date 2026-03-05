# SPDX-License-Identifier: GPL-3.0
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(CMakeSamples)

message(STATUS CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../Modules")
include(LinuxDistro)

add_definitions("-DCMAKE_SAMPLES=1")
add_definitions(${LINUX_DISTRO_CFLAGS})

add_subdirectory(execute)
add_subdirectory(function)
add_subdirectory(string)

add_library(lib1 STATIC lib1.c)

include_directories(".")
