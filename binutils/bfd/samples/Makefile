# SPDX-License-Identifier: GPL-3.0
CC := gcc
__USE_PROC_HELPERS__ = y

include ../bfd.mk

target-y :=
target-y += bfd_init
target-y += build_id
target-y += bfd_symbol_info
target-y += bfd_get_start_address
target-y += bfd_get_flavour
target-y += bfd_elf_bfd_from_remote_memory
target-y += phdr
target-y += sections
target-y += symbol symbol-value
target-y += breakpoint_tst breakpoint_bfd
target-y += reloc
target-y += reloc-name
target-y += bfd_print_symbol_vandf

CFLAGS :=
CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable

LDFLAGS += -lbfd
LDFLAGS += -lpthread

# FIXME: /usr/include/bfd.h may include these lines. There must be a better way
# to fix this.
#  /* PR 14072: Ensure that config.h is included first.  */
#  #if !defined PACKAGE && !defined PACKAGE_VERSION
#  # error config.h must be included before this header
#  #endif
CFLAGS += -DPACKAGE=1

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

# TODO: use this
define bfd_strip
  @strip $(1) -o $(1).strip
endef

include ../../../template/main.mk

bfd_helpers.o: bfd_helpers.h

bfd_init: bfd_init.o bfd_helpers.o
build_id: build_id.o bfd_helpers.o
bfd_symbol_info: bfd_symbol_info.o bfd_helpers.o ${PROC_HELPERS}
bfd_get_start_address: bfd_get_start_address.o
bfd_get_flavour: bfd_get_flavour.o
bfd_elf_bfd_from_remote_memory: bfd_elf_bfd_from_remote_memory.o
phdr: phdr.o
sections: sections.o
symbol: symbol.o bfd_helpers.o ${PROC_HELPERS}
symbol-value: symbol-value.o bfd_helpers.o ${PROC_HELPERS}
breakpoint_tst: breakpoint_tst.o
breakpoint_bfd: breakpoint_bfd.o
reloc: reloc.o
reloc-name: reloc-name.o
bfd_print_symbol_vandf: bfd_print_symbol_vandf.o bfd_helpers.o ${PROC_HELPERS}
