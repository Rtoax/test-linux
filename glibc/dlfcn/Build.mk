include helpers.mk

subdir-y := hacking

target-y := hello
target-y += socket
target-y += malloc
target-y += vdso
target-y += dlinfo

target-${IS_AARCH64} += dlsym-RTLD_DEFAULT

prog-y += ${target-y}

target-libso-y := libhello.so.0.1
target-libso-y += libglibc.so.6

libhello.so.0.1-objs := libhello.so.o
libglibc.so.6-objs := libc.so.o

socket-objs := libc.o
dlinfo-objs := ${PROC_HELPERS}

CFLAGS += -I../../
CFLAGS += -I../../fs/procfs/

LDFLAGS := -ldl
