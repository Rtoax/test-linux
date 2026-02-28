message(STATUS "cuRand")
link_libraries(cuda_helpers curand)

add_executable(rand rand.cu)
