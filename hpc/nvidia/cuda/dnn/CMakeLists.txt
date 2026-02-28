message(STATUS "DNN")
link_libraries(cuda_helpers)

find_path(CUDNN_INCLUDE_DIR
    NAMES cudnn.h cudnn_version.h
    PATHS /usr/include/ /usr/local/include/
)

if(CUDNN_INCLUDE_DIR)
    link_libraries(cudnn)
    include_directories(${CUDNN_INCLUDE_DIR})
    add_executable(dnn_version version.cu)
    # Conflict with samples/version.cu
    set_target_properties(dnn_version PROPERTIES
        OUTPUT_NAME "version"
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dnn/
    )
endif()
