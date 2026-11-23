# SPDX-License-Identifier: GPL-2.0-or-later
find_program(GZIP gzip REQUIRED)
set(MAN_DOCS)
set(MAN_DOCS plotcake.8)

file(GLOB FILES ${MAN_DOCS})

set(GZFILES "")
foreach(FIL ${FILES})
  get_filename_component(NAME ${FIL} NAME)
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.gz
    COMMAND ${GZIP} -c ${FIL} > ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.gz
    DEPENDS ${FIL})
  list(APPEND GZFILES "${CMAKE_CURRENT_BINARY_DIR}/${NAME}.gz")
endforeach()
add_custom_target(man_man DEPENDS ${GZFILES})
install(FILES ${GZFILES} DESTINATION ${CMAKE_INSTALL_MANDIR}/man8)
