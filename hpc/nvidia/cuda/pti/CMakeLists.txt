link_libraries(cuda_helpers cupti)

set(EXECUTIONS activity subscribe)
# FIXME: LUCA not support yet, use -DUSE_LUCA=ON
if(NOT USE_LUCA)
  list(APPEND EXECUTIONS range sampling)
endif()

message(STATUS "cuPTI: ${EXECUTIONS}")

foreach(tgt ${EXECUTIONS})
  add_executable(${tgt} ${tgt}.cu)
endforeach()
add_executable(pti_version version.cu)

# Conflict with samples/version.cu
set_target_properties(pti_version PROPERTIES
    OUTPUT_NAME "version"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pti/
)
