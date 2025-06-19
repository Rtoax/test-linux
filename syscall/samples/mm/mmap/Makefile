include ../../../../kconfig.mk

TARGETS :=
TARGETS += msync
TARGETS += fexecve
TARGETS += mmap-anon
TARGETS += mmap-file mremap-file
TARGETS += remap_file_pages
TARGETS += get_unmapped_page
TARGETS += mmap-multi-thread-copy
TARGETS += mmap-exec

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -lrt

CFLAGS_mremap-file := -DMREMAP=1

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
