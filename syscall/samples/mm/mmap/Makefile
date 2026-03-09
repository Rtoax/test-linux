include kconfig.mk

OUTPUT := .output/

target-y += msync
target-y += fexecve
target-y += mmap-anon
target-y += mmap-file mremap-file
target-y += remap_file_pages
target-y += get_unmapped_page
target-y += mmap-multi-thread-copy
target-y += mmap-exec

target-libso-y := libmmap_helpers.so
target-liba-y := libmmap_helpers.a

libmmap_helpers.a-objs := ${OUTPUT}mmap_helpers.a.o
libmmap_helpers.so-objs := ${OUTPUT}mmap_helpers.so.o

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

include main.mk

mmap_helpers.so.o: mmap_helpers.h
mmap_helpers.a.o: mmap_helpers.h

msync: ${OUTPUT}msync.o
fexecve: ${OUTPUT}fexecve.o
mmap-anon: ${OUTPUT}mmap-anon.o
mmap-file: ${OUTPUT}mmap-file.o
mremap-file: ${OUTPUT}mremap-file.o
remap_file_pages: ${OUTPUT}remap_file_pages.o
get_unmapped_page: ${OUTPUT}get_unmapped_page.o libmmap_helpers.a
mmap-multi-thread-copy: ${OUTPUT}mmap-multi-thread-copy.o
mmap-exec: ${OUTPUT}mmap-exec.o
