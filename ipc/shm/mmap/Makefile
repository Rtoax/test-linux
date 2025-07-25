targets :=
targets += shm-reader shm-writer
targets += mmap-reader mmap-writer

CFLAGS := -g -ggdb -O0
CFLAGS += -lrt

targets-test += test0

include ../../../template/main.mk

shm-reader: shm-reader.o
shm-writer: shm-writer.o
mmap-reader: mmap-reader.o
mmap-writer: mmap-writer.o

test0:
	$(call log_tgt_exe,TEST,,$(@))
	$(Q)./shm-writer && ./shm-reader
	$(Q)./mmap-writer && ./mmap-reader
