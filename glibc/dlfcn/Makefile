sub-dir := hacking

targets := hello
targets += socket
targets += malloc
targets += vdso
targets += dlinfo

ifneq ($(shell uname -m),aarch64)
  targets += dlsym-RTLD_DEFAULT
endif

targets-libso := libhello.so.0.1
targets-libso += libglibc.so.6

LDFLAGS := -ldl

CFLAGS += -I../../
CFLAGS += -I../../fs/procfs/

include ../../template/main.mk

hello: hello.o
socket: socket.o libc.o
malloc: malloc.o libc.o
vdso: vdso.o
dlinfo: dlinfo.o proc_helpers.o
dlsym-RTLD_DEFAULT: dlsym-RTLD_DEFAULT.o

libhello.so.0.1: libhello.so.o
libglibc.so.6: libc.so.o

proc_helpers.o: ../../fs/procfs/proc_helpers.o
	$(info We are in $(shell pwd))
	${Q}mv $(<) $(@)
