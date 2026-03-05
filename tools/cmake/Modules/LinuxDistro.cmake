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

  file(READ "/etc/os-release" OS_RELEASE_CONTENT)
  string(REGEX MATCH "VERSION_ID=[\"']?([0-9\\.]+)[\"']?" _ ${OS_RELEASE_CONTENT})

  if(CMAKE_MATCH_1)
    set(VERSION_ID_STR "${CMAKE_MATCH_1}")
  else()
    message(FATAL_ERROR "VERSION_ID not found, using default 0.0")
    set(VERSION_ID_STR "0.0")
  endif()

  if(VERSION_ID_STR MATCHES "^([0-9]+)\\.([0-9]+)$")
    set(OS_MAJOR "${CMAKE_MATCH_1}")
    set(OS_MINOR "${CMAKE_MATCH_2}")
  elseif(VERSION_ID_STR MATCHES "^([0-9]+)$")
    set(OS_MAJOR "${CMAKE_MATCH_1}")
    set(OS_MINOR "0")
  else()
    message(FATAL_ERROR "Unrecognized VERSION_ID format: ${VERSION_ID_STR}")
    set(OS_MAJOR "0")
    set(OS_MINOR "0")
  endif()

  string(TOUPPER ${LINUX_DISTRO} LINUX_DISTRO_UPPER)
  set(LINUX_DISTRO_CFLAGS)
  list(APPEND LINUX_DISTRO_CFLAGS "-D__${LINUX_DISTRO}__=1")
  list(APPEND LINUX_DISTRO_CFLAGS "-D__os_major__=${OS_MAJOR}")
  list(APPEND LINUX_DISTRO_CFLAGS "-D__os_minor__=${OS_MINOR}")

  message(STATUS "LINUX_DISTRO = ${LINUX_DISTRO}")
  message(STATUS "LINUX_DISTRO_UPPER = ${LINUX_DISTRO_UPPER}")
  message(STATUS "OS_MAJOR = ${OS_MAJOR}")
  message(STATUS "OS_MINOR = ${OS_MINOR}")
  message(STATUS "LINUX_DISTRO_CFLAGS = ${LINUX_DISTRO_CFLAGS}")
endif()
