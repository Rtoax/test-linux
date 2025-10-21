target-y :=
target-y += mmap
target-y += pmem_map_file

LDFLAGS := -lpmem

include ../../../template/main.mk

mmap: mmap.o
pmem_map_file: pmem_map_file.o
