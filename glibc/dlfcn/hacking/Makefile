target-y := dev

target-libso-y := libdev.so.1
target-libso-y += libdev_hack.so

target-test-y := run0

libdev.so.1-objs := libdev.so.o

CFLAGS_dev := -ldev
LDFLAGS_dev := libdev.so

include main.mk

dev: dev.o libdev.so.1

run0:
	${Q}./run.sh
