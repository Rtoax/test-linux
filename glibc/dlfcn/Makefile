include arch.mk

subdir-y := hacking

target-y := hello
target-y += socket
target-y += malloc
target-y += vdso
target-y += dlinfo

target-${IS_AARCH64} += dlsym-RTLD_DEFAULT

target-libso-y := libhello.so.0.1
target-libso-y += libglibc.so.6

libhello.so.0.1-objs := libhello.so.o
libglibc.so.6-objs := libc.so.o

socket-objs := libc.o
dlinfo-objs := proc_helpers.o

LDFLAGS := -ldl

CFLAGS += -I../../
CFLAGS += -I../../fs/procfs/

include main.mk

proc_helpers.o: ../../fs/procfs/proc_helpers.o
	$(info We are in $(shell pwd))
	${Q}mv $(<) $(@)
