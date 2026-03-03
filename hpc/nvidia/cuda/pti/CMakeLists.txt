link_libraries(cuda_helpers cupti)

set(EXECUTIONS activity subscribe)
# FIXME: LUCA not support yet, use -DUSE_LUCA=ON
if(NOT USE_LUCA)
  list(APPEND EXECUTIONS range sampling)
endif()

message(STATUS "cuPTI: ${EXECUTIONS}")

function(compile_tgt class name)
  add_executable(${class}_${name} ${name}.cu)
  set_target_properties(${class}_${name} PROPERTIES
    OUTPUT_NAME ${name}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${class}/
  )
endfunction()

foreach(tgt ${EXECUTIONS})
  compile_tgt(pti ${tgt})
endforeach()
