# SPDX-License-Identifier: GPL-3.0
target-y += R_X86_64
target-y += R_X86_64_64
target-y += R_X86_64_32S
target-y += R_X86_64_PC32
target-y += R_X86_64_PLT32
target-y += R_X86_64_COPY
target-y += R_X86_64_JUMP_SLOT
target-y += R_X86_64_GLOB_DAT

obj-o += R_X86_64_32.o
obj-o += R_X86_64_PLT32.o
obj-o += R_X86_64_GOTPCRELX.o

obj-s-o += R_X86_64_32.s.o
obj-s-o += R_X86_64_64.s.o
obj-s-o += R_X86_64_GOT32.s.o R_X86_64_GOTPC32.s.o
obj-s-o += R_X86_64_GOTPLT64.s.o
obj-s-o += R_X86_64_GOTOFF64.s.o
obj-s-o += R_X86_64_REX_GOTPCRELX.s.o
obj-s-o += R_X86_64_PLT32.s.o
obj-s-o += R_X86_64_PLTOFF64.s.o

prep-y := $(patsubst %,${OUTPUT}%, ${obj-o} ${obj-s-o})

prog-y := R_X86_64_64.sh
prog-y += R_X86_64_PC32.sh

PROG_ARGS_R_X86_64_64.sh := ${OUTPUT}
PROG_ARGS_R_X86_64_PC32.sh := ${OUTPUT}

CFLAGS += -O0
CFLAGS += -I..

ifneq ($(shell uname -m),x86_64)
  $(warning Try compile on $(shell uname -m))
  obj-s-o :=
endif

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

CFLAGS_R_X86_64_JUMP_SLOT := -fplt
# or use libc.so like:
# int getchar(void) __attribute__ ((noplt));
CFLAGS_R_X86_64_GOTPCRELX := -fpic -fno-plt
CFLAGS_R_X86_64_GLOB_DAT := -fpic -fno-plt
