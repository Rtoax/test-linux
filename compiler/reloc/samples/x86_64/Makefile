# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk


TARGETS :=
TARGETS_O :=
TARGETS_SO :=
TARGETS_A :=
TARGETS_S_O :=

CC := gcc
AS := as

AS_ARGS :=
CFLAGS :=
LDFLAGS :=
CFLAGS_PIE :=
LDFLAGS_PIE :=

TARGETS += R_X86_64_64
TARGETS += R_X86_64_32S
TARGETS += R_X86_64_PC32
TARGETS += R_X86_64_COPY
TARGETS += R_X86_64_JUMP_SLOT
TARGETS += R_X86_64_GLOB_DAT

TARGETS_O += R_X86_64_32.o
TARGETS_O += R_X86_64_PLT32.o
TARGETS_O += R_X86_64_GOTPCRELX.o

TARGETS_S_O += R_X86_64_32.So
TARGETS_S_O += R_X86_64_64.So
TARGETS_S_O += R_X86_64_GOT32.So R_X86_64_GOTPC32.So
TARGETS_S_O += R_X86_64_GOTPLT64.So
TARGETS_S_O += R_X86_64_GOTOFF64.So
TARGETS_S_O += R_X86_64_REX_GOTPCRELX.So
TARGETS_S_O += R_X86_64_PLT32.So
TARGETS_S_O += R_X86_64_PLTOFF64.So

ifneq ($(shell uname -m),x86_64)
  $(error Try compile on $(shell uname -m))
endif

AS_ARGS += --64

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifdef PIE
  CFLAGS_PIE += -fpie
  LDFLAGS_PIE += -pie
else
  CFLAGS_PIE += -no-pie
  LDFLAGS_PIE += -no-pie
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

define print_elf_reloc
	@echo -e "# $(1)" > ${1}.reloc
	@readelf --relocs --wide $(1) >> ${1}.reloc
endef

.PHONY: build
build: ${TARGETS_SO} ${TARGETS_A} ${TARGETS} ${TARGETS_O} ${TARGETS_S_O}
	@echo -e " \033[1;33m Done \033[m"

R_X86_64_JUMP_SLOT: R_X86_64_JUMP_SLOT.o
R_X86_64_GLOB_DAT: R_X86_64_GLOB_DAT.o

R_X86_64_64: R_X86_64_64.o
R_X86_64_32S: R_X86_64_32S.o
R_X86_64_PC32: R_X86_64_PC32.o
R_X86_64_COPY: R_X86_64_COPY.o

R_X86_64_PLT32.o: R_X86_64_PLT32.c
R_X86_64_GOTPCRELX.o: R_X86_64_GOTPCRELX.c

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -S $(<) -o $(<:.c=.c.s) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
	@$(call print_elf_reloc,$(@))

%.So: %.S
	@echo -e "  AS  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@${AS} ${AS_ARGS} -o $(@) $(<)
	@$(call print_elf_reloc,$(@))

%.obj: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_PIE) $(LDFLAGS_$(*))
	@$(call print_elf_reloc,$(@))

$(TARGETS_SO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) -shared -fPIC $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_A): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	@ar rcs $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO) $(TARGETS_A) ${TARGETS_O} ${TARGETS_S_O}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_SO} ${TARGETS_A} ${TARGETS_O} ${TARGETS_S_O} \
		*.o *.obj *.reloc *.So *.c.s
