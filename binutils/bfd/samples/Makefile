# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


include bfd.mk

TARGETS :=
TARGETS += bfd_init
TARGETS += build_id
TARGETS += bfd_symbol_info
TARGETS += bfd_get_start_address
TARGETS += bfd_get_flavour
TARGETS += bfd_elf_bfd_from_remote_memory
TARGETS += phdr
TARGETS += sections
TARGETS += symbol symbol-value
TARGETS += breakpoint_tst breakpoint_bfd
TARGETS += reloc
TARGETS += reloc-name
TARGETS += bfd_print_symbol_vandf

CC := gcc
LIBS_DIR := ../../../libs/

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0
CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable
CFLAGS += -lbfd
CFLAGS += -lpthread
CFLAGS += -I${LIBS_DIR}

# FIXME: /usr/include/bfd.h may include these lines. There must be a better way
# to fix this.
#  /* PR 14072: Ensure that config.h is included first.  */
#  #if !defined PACKAGE && !defined PACKAGE_VERSION
#  # error config.h must be included before this header
#  #endif
CFLAGS += -DPACKAGE=1

include ../../../elf/pie.mk

bfd_init-ret-magic := $(findstring 1,$(call probe_bfd_init_ret_magic))
ifeq ($(bfd_init-ret-magic),1)
  CFLAGS += -DBFD_INIT_RET_INIT_MAGIC=1
endif
has-bfd_section_vma := $(findstring 1,$(call probe_bfd_has_bfd_section_vma))
ifeq ($(has-bfd_section_vma),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_VMA=1
endif
has-bfd_section_vma-2 := $(findstring 1,$(call probe_bfd_has_bfd_section_vma2))
ifeq ($(has-bfd_section_vma-2),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_VMA2=1
endif
has-bfd_set_section_vma := $(findstring 1,$(call probe_bfd_has_bfd_set_section_vma))
ifeq ($(has-bfd_set_section_vma),1)
  CFLAGS += -DBFD_HAS_BFD_SET_SECTION_VMA=1
endif
has-bfd_set_section_vma2 := $(findstring 1,$(call probe_bfd_has_bfd_set_section_vma2))
ifeq ($(has-bfd_set_section_vma2),1)
  CFLAGS += -DBFD_HAS_BFD_SET_SECTION_VMA2=1
endif
has-bfd_section_lma := $(findstring 1,$(call probe_bfd_has_bfd_section_lma))
ifeq ($(has-bfd_section_lma),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_LMA=1
endif
has-bfd_section_lma2 := $(findstring 1,$(call probe_bfd_has_bfd_section_lma2))
ifeq ($(has-bfd_section_lma2),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_LMA2=1
endif
has-bfd_section_name := $(findstring 1,$(call probe_bfd_has_bfd_section_name))
ifeq ($(has-bfd_section_name),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_NAME=1
endif
has-bfd_section_name2 := $(findstring 1,$(call probe_bfd_has_bfd_section_name2))
ifeq ($(has-bfd_section_name2),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_NAME2=1
endif
has-bfd_section_size := $(findstring 1,$(call probe_bfd_has_bfd_section_size))
ifeq ($(has-bfd_section_size),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_SIZE=1
endif
has-bfd_section_size2 := $(findstring 1,$(call probe_bfd_has_bfd_section_size2))
ifeq ($(has-bfd_section_size2),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_SIZE2=1
endif
has-bfd_section_alignment := $(findstring 1,$(call probe_bfd_has_bfd_section_alignment))
ifeq ($(has-bfd_section_alignment),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_ALIGNMENT=1
endif
has-bfd_section_alignment2 := $(findstring 1,$(call probe_bfd_has_bfd_section_alignment2))
ifeq ($(has-bfd_section_alignment2),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_ALIGNMENT2=1
endif
has-bfd_section_flags := $(findstring 1,$(call probe_bfd_has_bfd_section_flags))
ifeq ($(has-bfd_section_flags),1)
  CFLAGS += -DBFD_HAS_BFD_SECTION_FLAGS=1
endif
has-bfd_asymbol_section := $(findstring 1,$(call probe_bfd_has_bfd_asymbol_section))
ifeq ($(has-bfd_asymbol_section),1)
  CFLAGS += -DBFD_HAS_BFD_ASYMBOL_SECTION=1
endif
has-bfd_get_symbol_version_string := $(findstring 1,$(call probe_bfd_has_bfd_get_symbol_version_string))
ifeq ($(has-bfd_get_symbol_version_string),1)
  CFLAGS += -DBFD_HAS_BFD_GET_SYMBOL_VERSION_STRING=1
endif

include ../../binutils.mk

CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

CFLAGS_bfd_print_symbol_vandf := -DTEST_bfd_print_symbol_vandf=1
CFLAGS_symbol-value := -DTEST_SYMBOL_VALUE=1

define bfd_strip
  @strip $(1) -o $(1).strip
endef

$(info CFLAGS=${CFLAGS})
$(info LDFLAGS=${LDFLAGS})

build: ${TARGETS}
	@echo -e "  CFLAGS=${CFLAGS}"
	@echo -e "  LDFLAGS=${LDFLAGS}"
	@echo -e " \033[1;33m Done \033[m"

bfd_helpers.o: bfd_helpers.h

bfd_init: bfd_init.o bfd_helpers.o
build_id: build_id.o bfd_helpers.o
bfd_symbol_info: bfd_symbol_info.o bfd_helpers.o libtest-linux-c.a
bfd_get_start_address: bfd_get_start_address.o
bfd_get_flavour: bfd_get_flavour.o
bfd_elf_bfd_from_remote_memory: bfd_elf_bfd_from_remote_memory.o
phdr: phdr.o
sections: sections.o
symbol: symbol.o bfd_helpers.o libtest-linux-c.a
symbol-value: symbol-value.o bfd_helpers.o libtest-linux-c.a
breakpoint_tst: breakpoint_tst.o
breakpoint_bfd: breakpoint_bfd.o
reloc: reloc.o
reloc-name: reloc-name.o
bfd_print_symbol_vandf: bfd_print_symbol_vandf.o bfd_helpers.o libtest-linux-c.a

include ${LIBS_DIR}/libs.mk

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))
	$(call bfd_strip,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.out *.strip *.a

