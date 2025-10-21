include ../../../../template/kconfig.mk

target-y :=
target-y += msync
target-y += fexecve
target-y += mmap-anon
target-y += mmap-file mremap-file
target-y += remap_file_pages
target-y += get_unmapped_page
target-y += mmap-multi-thread-copy
target-y += mmap-exec

CFLAGS := -pthread
CFLAGS += -lrt

CFLAGS_mremap-file := -DMREMAP=1

ifdef OVERFLOW
  CFLAGS += -DOVERFLOW=1
endif

ifeq ($(CONFIG_ANON_VMA_NAME),y)
  CFLAGS += -DCONFIG_ANON_VMA_NAME=1
endif

# mmap-exec never should has -pg cflag, because copy text to exec-mem will
# change the address.
# CFLAGS_mmap-exec := -pg

include ../../../../template/main.mk

msync: msync.o
fexecve: fexecve.o
mmap-anon: mmap-anon.o
mmap-file: mmap-file.o
mremap-file: mremap-file.o
remap_file_pages: remap_file_pages.o
get_unmapped_page: get_unmapped_page.o mmap_helpers.o
mmap-multi-thread-copy: mmap-multi-thread-copy.o
mmap-exec: mmap-exec.o
