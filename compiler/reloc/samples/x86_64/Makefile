# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS_O :=
TARGETS_S_O :=

CC := gcc
AS := as

CFLAGS :=
LDFLAGS :=
CFLAGS_PIE :=
LDFLAGS_PIE :=

TARGETS += R_X86_64
TARGETS += R_X86_64_64
TARGETS += R_X86_64_32S
TARGETS += R_X86_64_PC32
TARGETS += R_X86_64_PLT32
TARGETS += R_X86_64_COPY
TARGETS += R_X86_64_JUMP_SLOT
TARGETS += R_X86_64_GLOB_DAT

TARGETS_O += R_X86_64_32.o
TARGETS_O += R_X86_64_PLT32.o
TARGETS_O += R_X86_64_GOTPCRELX.o

TARGETS_S_O += R_X86_64_32.S.o
TARGETS_S_O += R_X86_64_64.S.o
TARGETS_S_O += R_X86_64_GOT32.S.o R_X86_64_GOTPC32.S.o
TARGETS_S_O += R_X86_64_GOTPLT64.S.o
TARGETS_S_O += R_X86_64_GOTOFF64.S.o
TARGETS_S_O += R_X86_64_REX_GOTPCRELX.S.o
TARGETS_S_O += R_X86_64_PLT32.S.o
TARGETS_S_O += R_X86_64_PLTOFF64.S.o

TARGETS_PREP := ${TARGETS_O} ${TARGETS_S_O}
TARGETS_SHELL := R_X86_64_64.sh
TARGETS_SHELL += R_X86_64_PC32.sh

CFLAGS += -O0
CFLAGS += -I..

ifneq ($(shell uname -m),x86_64)
  $(warning Try compile on $(shell uname -m))
  TARGETS_S_O :=
endif

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifndef PIE
  NOPIE ?= 1
endif
include ../../../../elf/pie.mk

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

CFLAGS_R_X86_64_JUMP_SLOT := -fplt
# or use libc.so like:
# int getchar(void) __attribute__ ((noplt));
CFLAGS_R_X86_64_GOTPCRELX := -fpic -fno-plt
CFLAGS_R_X86_64_GLOB_DAT := -fpic -fno-plt

include ../../../../template/main.mk

R_X86_64: R_X86_64.o

R_X86_64_JUMP_SLOT: R_X86_64_JUMP_SLOT.o
R_X86_64_GLOB_DAT: R_X86_64_GLOB_DAT.o

R_X86_64_64: R_X86_64_64.o
R_X86_64_32S: R_X86_64_32S.o
R_X86_64_PC32: R_X86_64_PC32.o
R_X86_64_COPY: R_X86_64_COPY.o
R_X86_64_PLT32: R_X86_64_PLT32.o

R_X86_64_PLT32.o: R_X86_64_PLT32.c
R_X86_64_GOTPCRELX.o: R_X86_64_GOTPCRELX.c

# TODO: use it
define print_elf_reloc
	@echo -e "# $(1)" > ${1}.reloc
	@readelf --relocs --wide $(1) >> ${1}.reloc
endef

%.reloc:
	@echo -e "  READELF  \033[1;32m$(@)\033[m"
	@$(call print_elf_reloc,$(@))
