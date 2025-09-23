# SPDX-License-Identifier: GPL-3.0
include ../template/kconfig.mk

sub-dir := aslr
sub-dir += rss
sub-dir += cache
sub-dir += hugepage
sub-dir += oom
sub-dir += tcmalloc
sub-dir += tlb
sub-dir += jemalloc
sub-dir += vmalloc
sub-dir += pmem

targets := virt2phy
targets-liba := libtest-linux-mm.a
targets-liba += proc_helpers.a

CFLAGS += -DMMAP_HELPERS_HDR=mmap_helpers.h

CFLAGS_virt2phy := -DHAVE_MAIN=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_C=1
CFLAGS_virt2phy += -DHAVE_LIB_TEST_LINUX_NUMA=1
CFLAGS_virt2phy += -DHAVE_MMAP_HELPERS=1
CFLAGS_virt2phy += -I../numa/
LDFLAGS_virt2phy += -lnuma

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

include ../template/main.mk

virt2phy: virt2phy.o proc_helpers.a numa.a.1 mmap_helpers.o
libtest-linux-mm.a: virt2phy.a.o
proc_helpers.a: proc_helpers.a.o
numa.a.1:
	$(Q)make -C ../numa numa.a
	$(Q)cp ../numa/numa.a numa.a.1
