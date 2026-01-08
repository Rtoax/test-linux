cmake_minimum_required(VERSION 3.0)
project(hello)

set(LSCC_PATH $ENV{LUCA_PATH})
set(CMAKE_CXX_COMPILER ${LSCC_PATH}/lsgpu_llvm/bin/lscc)
set(LSCC_COMPILE_FLAGS -x luca)
add_compile_options(${LSCC_COMPILE_FLAGS})

File(GLOB SRCS hello.cpp)
add_executable(hello ${SRCS})
