__USE_PROC_HELPERS__ = y

target-y := statfs
target-y += fstatfs

CFLAGS := -pthread

include ../../../template/main.mk

statfs: statfs.o ${PROC_HELPERS}
fstatfs: fstatfs.o
