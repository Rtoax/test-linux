target-y := dev

target-libso-y := libdev.so.1
target-libso-y += libdev_hack.so

CC := gcc

CFLAGS :=

LDFLAGS :=

CFLAGS_dev := -ldev
LDFLAGS_dev := libdev.so

target-test-y := run0

include ../../../template/main.mk

libdev.so.1: libdev.so.o
dev: dev.o libdev.so.1

run0:
	${Q}./run.sh
