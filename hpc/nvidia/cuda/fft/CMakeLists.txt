message(STATUS "FFT")
link_libraries(cuda_helpers cufft)

add_executable(fft fft.cu)
