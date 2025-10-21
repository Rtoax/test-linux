# SPDX-License-Identifier: GPL-3.0
target-y :=
obj-o :=
obj-s-o :=

CC := gcc
AS := as

CFLAGS :=
LDFLAGS :=

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

obj-s-o += R_X86_64_32.S.o
obj-s-o += R_X86_64_64.S.o
obj-s-o += R_X86_64_GOT32.S.o R_X86_64_GOTPC32.S.o
obj-s-o += R_X86_64_GOTPLT64.S.o
obj-s-o += R_X86_64_GOTOFF64.S.o
obj-s-o += R_X86_64_REX_GOTPCRELX.S.o
obj-s-o += R_X86_64_PLT32.S.o
obj-s-o += R_X86_64_PLTOFF64.S.o

target-prep-y := ${obj-o} ${obj-s-o}
target-shell-y := R_X86_64_64.sh
target-shell-y += R_X86_64_PC32.sh

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
	$(call log_tgt_exe,READELF,,$(@))
	@$(call print_elf_reloc,$(@))
