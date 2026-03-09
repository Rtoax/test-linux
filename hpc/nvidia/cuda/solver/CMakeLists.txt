message(STATUS "cuSolver")
link_libraries(cuda_helpers cusolver)

add_executable(solver solver.cu)
add_executable(solverSp solverSp.cu)
