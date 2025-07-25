# SPDX-License-Identifier: GPL-3.0
targets :=
targets += R_AARCH64
targets += R_AARCH64_JUMP_SLOT
targets += R_AARCH64_ABS64
targets += R_AARCH64_PREL64
targets += R_AARCH64_CALL26
targets += R_AARCH64_ADR_PREL_PG_HI21

CC := gcc

CFLAGS :=
LDFLAGS :=
CFLAGS += -I..
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

# TODO: use it
define print_elf_reloc
  @echo -e "# $(1)" > ${1}.reloc
  @readelf --relocs --wide $(1) >> ${1}.reloc
endef

include ../../../../template/main.mk

R_AARCH64: R_AARCH64.o
R_AARCH64_JUMP_SLOT: R_AARCH64_JUMP_SLOT.o
R_AARCH64_ABS64: R_AARCH64_ABS64.o
R_AARCH64_PREL64: R_AARCH64_PREL64.o
R_AARCH64_CALL26: R_AARCH64_CALL26.o
R_AARCH64_ADR_PREL_PG_HI21: R_AARCH64_ADR_PREL_PG_HI21.o
