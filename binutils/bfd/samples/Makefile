SHELL = bash

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

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0
CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable
CFLAGS += -lbfd

# FIXME: /usr/include/bfd.h may include these lines. There must be a better way
# to fix this.
#  /* PR 14072: Ensure that config.h is included first.  */
#  #if !defined PACKAGE && !defined PACKAGE_VERSION
#  # error config.h must be included before this header
#  #endif
CFLAGS += -DPACKAGE=1

ifdef PIE
  CFLAGS += -pie -fPIE
  LDFLAGS += -pie -fPIE
endif

ifdef NOPIE
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
  ifdef PIE
    $(error "Could no specify PIE and NOPIE at the same time")
  endif
endif

# Get binutils version
BINUTILS_VERSION = $(shell ld -v | grep -o [0-9].[0-9]\. | sed -n '1p')
BINUTILS_VERSION_MAJOR = $(shell echo ${BINUTILS_VERSION} | awk -F '.' '{print $$1}')
BINUTILS_VERSION_MINOR = $(shell echo ${BINUTILS_VERSION} | awk -F '.' '{print $$2}')

$(info Binutils version ${BINUTILS_VERSION_MAJOR}.${BINUTILS_VERSION_MINOR})
ifneq (${BINUTILS_VERSION_MAJOR},2)
  $(error Not support binutils ${BINUTILS_VERSION})
endif

CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

define bfd_strip
  @strip $(1) -o $(1).strip
endef

build: ${TARGETS}
	@echo -e "  CFLAGS=${CFLAGS}"
	@echo -e "  LDFLAGS=${LDFLAGS}"
	@echo -e " \033[1;33m Done \033[m"

bfd_init: bfd_init.o helpers.o
build_id: build_id.o helpers.o
bfd_symbol_info: bfd_symbol_info.o proc.o helpers.o
bfd_get_start_address: bfd_get_start_address.o
bfd_get_flavour: bfd_get_flavour.o
bfd_elf_bfd_from_remote_memory: bfd_elf_bfd_from_remote_memory.o
phdr: phdr.o
sections: sections.o
symbol: symbol.o proc.o helpers.o
symbol-value: symbol-value.o proc.o helpers.o
breakpoint_tst: breakpoint_tst.o
breakpoint_bfd: breakpoint_bfd.o
reloc: reloc.o
reloc-name: reloc-name.o
bfd_print_symbol_vandf: bfd_print_symbol_vandf.o proc.o

CFLAGS_bfd_print_symbol_vandf := -DTEST_bfd_print_symbol_vandf=1
CFLAGS_symbol-value := -DTEST_SYMBOL_VALUE=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))
	$(call bfd_strip,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.out *.strip

