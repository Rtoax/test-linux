message(STATUS "PTX")
link_libraries(cuda_helpers)

add_executable(globaltimer globaltimer.cu)
add_executable(laneid laneid.cu)
