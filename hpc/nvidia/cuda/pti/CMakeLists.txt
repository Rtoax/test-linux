link_libraries(cuda_helpers cupti)

set(EXECUTIONS activity subscribe)
# FIXME: LUCA not support yet
if(NOT USE_CU_BRIDGE)
  list(APPEND EXECUTIONS range sampling)
endif()

message(STATUS "cuPTI: ${EXECUTIONS}")

foreach(tgt ${EXECUTIONS})
  add_cuda_sample(pti ${tgt})
endforeach()
