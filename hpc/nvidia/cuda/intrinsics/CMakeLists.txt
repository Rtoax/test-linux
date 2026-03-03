link_libraries(cuda_helpers)

set(EXECUTIONS bfloat16 complex double fp128 fp4 fp6 fp8 half int simd)

message(STATUS "CUDA intrinsics: ${EXECUTIONS}")

foreach(tgt ${EXECUTIONS})
  add_cuda_sample(intrinsics ${tgt})
endforeach()
