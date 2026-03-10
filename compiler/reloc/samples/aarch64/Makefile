# SPDX-License-Identifier: GPL-3.0
target-y += R_AARCH64
target-y += R_AARCH64_JUMP_SLOT
target-y += R_AARCH64_ABS64
target-y += R_AARCH64_PREL64
target-y += R_AARCH64_CALL26
target-y += R_AARCH64_ADR_PREL_PG_HI21

CFLAGS += -I..
CFLAGS += -march=native

ifdef VERBOSE
  CFLAGS += -Q
  LDFLAGS += -Q
endif

# TODO: use it
define print_elf_reloc
  @echo -e "# $(1)" > ${1}.reloc
  @readelf --relocs --wide $(1) >> ${1}.reloc
endef

include main.mk
