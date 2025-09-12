CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(fstabd)

SET(CMAKE_C_COMPILER /usr/bin/clang)
SET(CMAKE_CXX_COMPILER /usr/bin/clang++)

add_subdirectory(src)

install(
TARGETS fstabd
RUNTIME DESTINATION /usr/sbin/
)

install(
PROGRAMS ${PROJECT_SOURCE_DIR}/fstabd.service
DESTINATION /usr/lib/systemd/system/
)

# uninstall targets
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
