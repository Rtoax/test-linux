TARGETS := dev

TARGETS_LIBSO := libdev.so.1
TARGETS_LIBSO += libdev_hack.so

CC := gcc

CFLAGS :=

LDFLAGS :=

CFLAGS_dev := -ldev
LDFLAGS_dev := libdev.so

TARGETS_TEST := run0

include ../../../template/main.mk

libdev.so.1: libdev.so.o
dev: dev.o libdev.so.1

run0:
	${Q}./run.sh
