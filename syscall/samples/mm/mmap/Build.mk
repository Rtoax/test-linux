include kconfig.mk
include helpers.mk

target-y += msync
target-y += fexecve
target-y += mmap-anon
target-y += mmap-file mremap-file
target-y += remap_file_pages
target-y += get_unmapped_page
target-y += mmap-multi-thread-copy
target-y += mmap-exec

get_unmapped_page-objs := ${MMAP_HELPERS}

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

LDFLAGS += -Wl,-rpath,$(shell pwd)
