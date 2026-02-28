message(STATUS "Samples")
link_libraries(cuda_helpers)

set(EXECUTIONS bfloat16 complex double fp128 fp4 fp6 fp8 half int simd)

foreach(tgt ${EXECUTIONS})
  add_executable(${tgt} ${tgt}.cu)
endforeach()
add_executable(intrinsics_float float.cu)

# Conflict with samples/version.cu
set_target_properties(intrinsics_float PROPERTIES
    OUTPUT_NAME "float"
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/intrinsics/
)
