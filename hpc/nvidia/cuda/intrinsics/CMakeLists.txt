link_libraries(cuda_helpers)

set(EXECUTIONS bfloat16 complex double fp128 fp4 fp6 fp8 half int simd)

message(STATUS "CUDA intrinsics: ${EXECUTIONS}")

foreach(tgt ${EXECUTIONS})
  add_cuda_sample(intrinsics ${tgt})
endforeach()

# set "--generate-code=arch=compute_80,code=[compute_80,sm_80]"
set_target_properties(intrinsics_bfloat16 PROPERTIES CUDA_ARCHITECTURES "80")
