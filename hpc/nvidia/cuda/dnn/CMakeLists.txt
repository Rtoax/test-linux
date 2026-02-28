message(STATUS "DNN")
link_libraries(cuda_helpers cudnn)

add_executable(dnn_version version.cu)
# Conflict with samples/version.cu
set_target_properties(dnn_version PROPERTIES
    OUTPUT_NAME "version"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_CURRENT_SOURCE_DIR}
)
