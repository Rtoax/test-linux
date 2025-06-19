TARGETS := statfs
TARGETS += fstatfs

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../fs/procfs/

include ../../../template/main.mk

statfs: statfs.o proc_helpers.o
fstatfs: fstatfs.o

proc_helpers.o: ../../../fs/procfs/proc_helpers.o
	$(info We are in $(shell pwd))
	mv $(<) $(@)
