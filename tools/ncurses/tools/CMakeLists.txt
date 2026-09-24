# SPDX-License-Identifier: GPL-2.0
cmake_minimum_required(VERSION 3.5)

project(Plotcake C)

set(CMAKE_INSTALL_PREFIX /usr)

set(SRC
  axis.c
  file.c
  keyboard.c
  lgroup.c
  line.c
  loadavg.c
  ltypes.c
  plot.c
  plotcake.c
  ram.c
  stdin.c
  utils.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON_C REQUIRED json-c)

find_library(MATH m)
find_library(NCURSESW ncursesw)
find_library(NCURSES ncurses)
find_library(PANEL panel)

add_definitions("-D_GNU_SOURCE")
if(NOT JSON_C_FOUND)
  message(WARNING "json-c was not found.")
else()
  add_definitions("-DHAVE_JSON_C=1")
endif()

add_executable(plotcake ${SRC})
target_link_libraries(plotcake PRIVATE ${MATH} ${NCURSESW} ${NCURSES} ${PANEL})
target_link_libraries(plotcake PRIVATE ${JSON_C_LIBRARIES})

install(TARGETS plotcake RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(tools)
