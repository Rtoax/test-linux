if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  execute_process(
    COMMAND sh -c "grep '^ID=' /etc/os-release | cut -d= -f2 | tr -d '\"'"
    OUTPUT_VARIABLE LINUX_DISTRO
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )

  if(NOT LINUX_DISTRO)
    execute_process(
      COMMAND sh -c "grep '^DISTRIB_ID=' /etc/lsb-release | cut -d= -f2 | tr -d '\"'"
      OUTPUT_VARIABLE LINUX_DISTRO
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_QUIET
    )
  endif()

  string(TOUPPER ${LINUX_DISTRO} LINUX_DISTRO_UPPER)

  message(STATUS "LINUX_DISTRO = ${LINUX_DISTRO}")
  message(STATUS "LINUX_DISTRO_UPPER = ${LINUX_DISTRO_UPPER}")
endif()
