# SPDX-License-Identifier: GPL-3.0
#
# Append definitions:
# - CFLAGS=
# - CFLAGS_A=
# - CFLAGS_SO=
# - CFLAGS_BPF=
# - CXXFLAGS=
# - CXXFLAGS_A=
# - CXXFLAGS_SO=
# - LDFLAGS=
# - LDFLAGS_SO=
# - LDXXFLAGS=
# - LDXXFLAGS_SO=
#
ifndef _CFLAGS_MK
_CFLAGS_MK = 1

include dir.mk

cflags_common += -I${TOPDIR}
cflags_common += -I${OUTPUT}
cflags_common += -D_GNU_SOURCE
cflags_common += -Werror -Wall

CFLAGS += ${cflags_common}
CFLAGS_A += ${cflags_common}
CFLAGS_SO += ${cflags_common}
CXXFLAGS += ${cflags_common}
CXXFLAGS_A += ${cflags_common}
CXXFLAGS_SO += ${cflags_common}
# C special, not for C++
CFLAGS += -Wstrict-prototypes

ifdef DEBUG
  $(info Compile with DEBUG=1)
  cflags_debug := -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS += ${cflags_debug}
  CFLAGS_A += ${cflags_debug}
  CFLAGS_SO += ${cflags_debug}
  CFLAGS_BPF += ${cflags_debug}
  CXXFLAGS += ${cflags_debug}
  CXXFLAGS_A += ${cflags_debug}
  CXXFLAGS_SO += ${cflags_debug}
endif

ifdef ERROR
  $(info Compile with ERROR=${ERROR})
  cflags_error := -DERROR=${ERROR}
  CFLAGS += ${cflags_error}
  CFLAGS_A += ${cflags_error}
  CFLAGS_SO += ${cflags_error}
  CFLAGS_BPF += ${cflags_error}
  CXXFLAGS += ${cflags_error}
endif

ifdef M32
  $(info Compile 32bit ELF M32=${M32})
  cflags_m32 := -m32 -DM32=${M32}
  CFLAGS += ${cflags_m32}
  CXXFLAGS += ${cflags_m32}
  LDFLAGS += ${cflags_m32}
  LDXXFLAGS += ${cflags_m32}
endif

ifdef FORCE
  $(info Compile with FORCE=${FORCE})
  cflags_force := -Wno-error -DFORCE=${FORCE}
  CFLAGS += ${cflags_force}
  CXXFLAGS += ${cflags_force}
endif

ifdef STATIC
  $(info Compile with STATIC=${STATIC})
  cflags_static := -static
  CFLAGS += ${cflags_static}
  CXXFLAGS += ${cflags_static}
  LDFLAGS += ${cflags_static}
  LDXXFLAGS += ${cflags_static}
endif

include pie.mk
CFLAGS += ${CFLAGS_PIE}
LDFLAGS += ${LDFLAGS_PIE}

ifdef DEBUG
  $(info CFLAGS = ${CFLAGS})
  $(info CFLAGS_A = ${CFLAGS_A})
  $(info CFLAGS_SO = ${CFLAGS_SO})
  $(info CFLAGS_BPF = ${CFLAGS_BPF})

  $(info CXXFLAGS = ${CXXFLAGS})
  $(info CXXFLAGS_A = ${CXXFLAGS_A})
  $(info CXXFLAGS_SO = ${CXXFLAGS_SO})

  $(info LDFLAGS = ${LDFLAGS})
  $(info LDXXFLAGS = ${LDXXFLAGS})
endif

export CFLAGS CFLAGS_A CFLAGS_SO CFLAGS_BPF CFLAGS_PIE
export CXXFLAGS CXXFLAGS_A CXXFLAGS_SO
export LDFLAGS LDXXFLAGS

endif # _CFLAGS_MK
