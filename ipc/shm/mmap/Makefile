TARGETS :=
TARGETS += shm-reader shm-writer
TARGETS += mmap-reader mmap-writer

CFLAGS := -g -ggdb -O0
CFLAGS += -lrt

TARGETS_TEST += test0

include ../../../template/main.mk

shm-reader: shm-reader.o
shm-writer: shm-writer.o
mmap-reader: mmap-reader.o
mmap-writer: mmap-writer.o

test0:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	./shm-writer && ./shm-reader
	./mmap-writer && ./mmap-reader
