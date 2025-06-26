# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk

TARGETS :=
TARGETS_O :=
TARGETS_S_O :=

CC := gcc
AS := as

AS_ARGS :=
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

AS_ARGS += --64
CFLAGS += -O0

ifneq ($(shell uname -m),x86_64)
  $(warning Try compile on $(shell uname -m))
  AS_ARGS :=
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

define print_elf_reloc
	@echo -e "# $(1)" > ${1}.reloc
	@readelf --relocs --wide $(1) >> ${1}.reloc
endef

.PHONY: build
build: ${TARGETS} ${TARGETS_O} ${TARGETS_S_O}
	@echo -e " \033[1;33m Done \033[m"

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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -S $(<) -o $(<:.c=.c.s) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
	@$(call print_elf_reloc,$(@))

%.S.o: %.S
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${AS} ${AS_ARGS} -o $(@) $(<)
	@$(call print_elf_reloc,$(@))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_PIE) $(LDFLAGS_$(*))
	@$(call print_elf_reloc,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	${Q}./R_X86_64_64.sh
	${Q}./R_X86_64_PC32.sh

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) ${TARGETS_O} ${TARGETS_S_O}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_O} ${TARGETS_S_O} \
		*.o *.reloc *.S.o *.c.s
