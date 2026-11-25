# SPDX-License-Identifier: GPL-2.0
cmake_minimum_required(VERSION 3.5)

project(Plotcake C)

set(CMAKE_INSTALL_PREFIX /usr)
set(CMAKE_INSTALL_MANDIR "/usr/share/man/")
set(CONFIG_JSON_C ON CACHE BOOL "Build with json-c")

set(SRC
  axis.c
  dialog.c
  file.c
  id-handler.c
  keyboard.c
  lgroup.c
  line.c
  loadavg.c
  ltypes.c
  plot.c
  plotcake.c
  ram.c
  scatter.c
  stdin.c
  utils.c
)

find_package(PkgConfig REQUIRED)
if(CONFIG_JSON_C)
  pkg_check_modules(JSON_C REQUIRED json-c)
endif()

find_library(MATH m)
find_library(NCURSESW ncursesw)
find_library(NCURSES ncurses)
find_library(PANEL panel)

add_definitions("-D_GNU_SOURCE")
if(CONFIG_JSON_C)
  if(NOT JSON_C_FOUND)
    message(FATAL_ERROR "json-c was not found.")
  else()
    add_definitions("-DHAVE_JSON_C=1")
  endif()
else()
  message(WARNING "Turn off json-c")
endif()

add_executable(plotcake ${SRC})
target_link_libraries(plotcake PRIVATE ${MATH} ${NCURSESW} ${NCURSES} ${PANEL})
target_link_libraries(plotcake PRIVATE ${JSON_C_LIBRARIES})

install(TARGETS plotcake RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

add_subdirectory(tools)
add_subdirectory(man)
