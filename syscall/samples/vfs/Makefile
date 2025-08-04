targets := statfs
targets += fstatfs

CFLAGS := -pthread

include ../../../template/main.mk

proc_helpers.o: proc_helpers.h
statfs: statfs.o proc_helpers.o
fstatfs: fstatfs.o
