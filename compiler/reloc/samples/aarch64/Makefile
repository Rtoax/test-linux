# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk

TARGETS :=
TARGETS_O :=
TARGETS_SO :=
TARGETS_A :=

CC := gcc

CFLAGS :=
LDFLAGS :=
CFLAGS_PIE :=
LDFLAGS_PIE :=

TARGETS += R_AARCH64
TARGETS += R_AARCH64_JUMP_SLOT
TARGETS += R_AARCH64_ABS64
TARGETS += R_AARCH64_PREL64
TARGETS += R_AARCH64_CALL26
TARGETS += R_AARCH64_ADR_PREL_PG_HI21

CFLAGS += -march=native

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

define print_elf_reloc
  @echo -e "# $(1)" > ${1}.reloc
  @readelf --relocs --wide $(1) >> ${1}.reloc
endef

.PHONY: build
build: ${TARGETS_SO} ${TARGETS_A} ${TARGETS} ${TARGETS_O}
	@echo -e " \033[1;33m Done \033[m"

R_AARCH64: R_AARCH64.o
R_AARCH64_JUMP_SLOT: R_AARCH64_JUMP_SLOT.o
R_AARCH64_ABS64: R_AARCH64_ABS64.o
R_AARCH64_PREL64: R_AARCH64_PREL64.o
R_AARCH64_CALL26: R_AARCH64_CALL26.o
R_AARCH64_ADR_PREL_PG_HI21: R_AARCH64_ADR_PREL_PG_HI21.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_PIE) $(CFLAGS_$(*))
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
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO) $(TARGETS_A) $(TARGETS_O)\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_SO} ${TARGETS_A} ${TARGETS_O} *.o *.obj *.reloc
