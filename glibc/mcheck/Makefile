TARGETS :=
TARGETS += mtrace
TARGETS += mprobe
TARGETS += mcheck_check_all

CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -lmcheck

LDFLAGS :=

CFLAGS_mprobe := -Wno-error=use-after-free

include ../../template/main.mk

mtrace: mtrace.o
mprobe: mprobe.o
mcheck_check_all: mcheck_check_all.o
