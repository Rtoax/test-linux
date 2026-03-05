link_libraries(cuda_helpers)

set(EXECUTIONS bfloat16 complex double fp4 fp6 fp8 half int simd)

if(SUPPORT___float128)
  list(APPEND EXECUTIONS fp128)
endif()

message(STATUS "CUDA intrinsics: ${EXECUTIONS}")

include(CDataType/__float128)

foreach(tgt ${EXECUTIONS})
  add_cuda_sample(intrinsics ${tgt})
endforeach()

# set "--generate-code=arch=compute_80,code=[compute_80,sm_80]"
set_target_properties(intrinsics_bfloat16 PROPERTIES CUDA_ARCHITECTURES "80")
