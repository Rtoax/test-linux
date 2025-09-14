targets := crc32b
targets += crc32w

CFLAGS += -g -ggdb
CFLAGS += -O3
CFLAGS += -pthread
CFLAGS += -march=armv8.1-a

include ../../../template/main.mk

kernel:
	${Q}make -C ${KERNELDIR} M=$(PWD) modules

crc32b: crc32b.o
crc32w: crc32w.o
