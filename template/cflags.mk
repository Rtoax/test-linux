# SPDX-License-Identifier: GPL-3.0
#
ifndef _CFLAGS_MK
_CFLAGS_MK = 1

CFLAGS += -I${OUTPUT}
CFLAGS += -D_GNU_SOURCE
CFLAGS += -Werror -Wall
# C special, not for C++
CFLAGS += -Wstrict-prototypes

CXXFLAGS += -I${OUTPUT}
CXXFLAGS += -D_GNU_SOURCE
CXXFLAGS += -Werror -Wall

ifdef DEBUG
  $(info Compile with DEBUG=1)
  CFLAGS += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS_A += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS_SO += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS_BPF += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS_A += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS_SO += -DDEBUG=${DEBUG} -O0 -g -ggdb
endif

ifdef ERROR
  $(info Compile with ERROR=${ERROR})
  CFLAGS += -DERROR=${ERROR}
  CFLAGS_A += -DERROR=${ERROR}
  CFLAGS_SO += -DERROR=${ERROR}
  CFLAGS_BPF += -DERROR=${ERROR}
  CXXFLAGS += -DERROR=${ERROR}
endif

ifdef M32
  $(info Compile 32bit ELF M32=${M32})
  CFLAGS += -m32 -DM32=${M32}
  CXXFLAGS += -m32 -DM32=${M32}
  LDFLAGS += -m32 -DM32=${M32}
  LDXXFLAGS += -m32 -DM32=${M32}
endif

ifdef FORCE
  $(info Compile with FORCE=${FORCE})
  CFLAGS += -Wno-error -DFORCE=${FORCE}
  CXXFLAGS += -Wno-error -DFORCE=${FORCE}
endif

ifdef STATIC
  $(info Compile with STATIC=${STATIC})
  CFLAGS += -static
  CXXFLAGS += -static
  LDFLAGS += -static
  LDXXFLAGS += -static
endif

include pie.mk
CFLAGS += ${CFLAGS_PIE}
LDFLAGS += ${LDFLAGS_PIE}

endif # _CFLAGS_MK
