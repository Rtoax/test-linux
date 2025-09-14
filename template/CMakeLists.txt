# SPDX-License-Identifier: GPL-3.0
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
add_definitions(-DHAVE_PRINTF=1)
add_definitions(-DCONFIG_MMU=1)

# GNU GCC version
if (CMAKE_COMPILER_IS_GNUCC)
	execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpfullversion -dumpversion
		OUTPUT_VARIABLE GCC_VERSION)
	string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
	list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
	list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)

	message(STATUS "cmake version=${CMAKE_VERSION}")

	set(GCC_VERSION "${GCC_MAJOR}.${GCC_MINOR}")
	message(STATUS "gcc version=${GCC_VERSION}")

	if (GCC_VERSION GREATER "4.7")
		message(STATUS "gcc version major=${GCC_MAJOR}")
		message(STATUS "gcc version minor=${GCC_MINOR}")
		add_definitions("-Wno-implicit-fallthrough")
	endif()
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message(STATUS "User clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	message(STATUS "User gcc")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
	message(STATUS "User Intel icc")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message(STATUS "User msvc")
endif()

# Check architecture
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
	message(STATUS "arch ${CMAKE_HOST_SYSTEM_PROCESSOR}")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
	message(STATUS "arch ${CMAKE_HOST_SYSTEM_PROCESSOR}")
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "riscv64")
	message(STATUS "arch ${CMAKE_HOST_SYSTEM_PROCESSOR}")
endif()

# Check compiler options
# 1. Use check_c_source_compiles()
# 2. Use command
set_property(GLOBAL APPEND_STRING PROPERTY global_cflags "-Wall -O0")
function(check_and_add_cflags flag)
	execute_process(
		COMMAND echo "int main(void) { return 0; }"
		COMMAND ${CMAKE_C_COMPILER} -x c -Wall - ${flag} -o -
		OUTPUT_VARIABLE /dev/null
		ERROR_VARIABLE /dev/null
		RESULT_VARIABLE NO_THIS_FLAG)
	# Or
	#try_compile(FLAG_AVAILABLE
	#	${CMAKE_CURRENT_BINARY_DIR}
	#	SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/xxx.c
	#	LINK_OPTIONS ${flag}
	#)
	#if(${FLAG_AVAILABLE})
	message(STATUS "NO_THIS_FLAG = ${NO_THIS_FLAG}")
	if(NOT ${NO_THIS_FLAG})
		message(STATUS "Compiler support ${flag}")
		set_property(GLOBAL APPEND_STRING PROPERTY global_cflags " ${flag}")
	else()
		message(STATUS "Compiler not support ${flag}")
	endif()
endfunction()
check_and_add_cflags("-no-this-flag")
check_and_add_cflags("-fno-omit-frame-pointer")
check_and_add_cflags("-mno-omit-leaf-frame-pointer")
get_property(global_cflags GLOBAL PROPERTY global_cflags)
message(STATUS "global_cflags = ${global_cflags}")

add_executable(main.user main.user.c)
