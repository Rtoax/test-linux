message(STATUS "cudaSamples")
link_libraries(cuda_helpers)

set(EXECUTIONS attribute cooperative device dim3 event float graph hello malloc
		mallocHost mallocManaged matrix memory mempool module oom p2p
		parallel properties rtc stream version __STDC__ __GNUC__)

foreach(tgt ${EXECUTIONS})
  add_executable(${tgt} ${tgt}.cu)
endforeach()

target_compile_definitions(matrix PRIVATE TEST_FP32)
