message(STATUS "cuDNN")
link_libraries(cuda_helpers)

find_path(CUDNN_INCLUDE_DIR
  NAMES cudnn.h cudnn_version.h
  PATHS /usr/include/ /usr/local/include/
)

if(CUDNN_INCLUDE_DIR)
  link_libraries(cudnn)
  include_directories(${CUDNN_INCLUDE_DIR})
  add_cuda_sample(dnn version)
endif()
