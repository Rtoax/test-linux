# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk
include ../kconfig.mk

sub-dir := rss
sub-dir += cache
sub-dir += hugepage
sub-dir += oom
sub-dir += tcmalloc
sub-dir += tlb
sub-dir += jemalloc
sub-dir += vmalloc
sub-dir += pmem

TARGETS :=
TARGETS_LIBA :=

TARGETS += virt2phy
TARGETS_LIBA += libtest-linux-mm.a
TARGETS_LIBA += proc_helpers.a

CC := gcc

CFLAGS :=
LDFLAGS :=

CFLAGS += -DMMAP_HELPERS_HDR=mmap_helpers.h

CFLAGS_virt2phy := -DHAVE_MAIN=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_C=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_NUMA=1
CFLAGS_virt2phy += -DHAVE_MMAP_HELPERS=1
CFLAGS_virt2phy += -lnuma

ifeq ($(CONFIG_DEVMEM),y)
  $(info CONFIG_DEVMEM=y)
  CFLAGS_virt2phy += -DCONFIG_DEVMEM=1
endif
# CONFIG_STRICT_DEVMEM=y is the default kernel configuration in general,
# disallows to access RAM area via /dev/mem or only allows first 1MB size
# of RAM.
ifeq ($(CONFIG_STRICT_DEVMEM),y)
  $(warning CONFIG_STRICT_DEVMEM=y, you don't allow r/w from/to /dev/mem)
  CFLAGS_virt2phy += -DCONFIG_STRICT_DEVMEM=1
endif
ifeq ($(CONFIG_MEMFD_CREATE),y)
  $(info CONFIG_MEMFD_CREATE=y)
  CFLAGS_virt2phy += -DCONFIG_MEMFD_CREATE=1
endif

MAKEFLAGS :=
NUMA_DIR := ../numa/

CFLAGS += -g
CFLAGS += -I${NUMA_DIR}

ifdef DEBUG
  CFLAGS += -DDEBUG=1
  MAKEFLAGS := DEBUG=1
endif

include ../elf/pie.mk

include ../template/subdir-header.mk

.PHONY: all
all: ${TARGETS_LIBA} ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

virt2phy: virt2phy.o proc_helpers.a libtest-linux-numa.a mmap_helpers.o
libtest-linux-mm.a: virt2phy.a.o
proc_helpers.a: proc_helpers.a.o

include ${NUMA_DIR}/numa.mk

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.obj: %.c
	@echo -e "  CC OBJ  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*)) -fPIC

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

include ../template/target-liba.mk

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_LIBA)\033[m"
	${Q}rm -f ${TARGETS} *.o *.a *.obj

include ../template/subdir-footer.mk
