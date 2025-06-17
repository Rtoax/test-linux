TARGETS :=
TARGETS += mmap
TARGETS += pmem_map_file

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g
LDFLAGS := -lpmem

include ../../../template/main.mk

mmap: mmap.o
pmem_map_file: pmem_map_file.o
