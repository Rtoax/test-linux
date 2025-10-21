target-y :=
ifeq ($(shell uname -m),x86_64)
  target-y += ARCH_SET_FS
  target-y += fsgsbase
endif

include ../../../template/main.mk

ARCH_SET_FS: ARCH_SET_FS.o
fsgsbase: fsgsbase.o
