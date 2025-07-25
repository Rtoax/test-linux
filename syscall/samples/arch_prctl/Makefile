targets :=
ifeq ($(shell uname -m),x86_64)
  targets += ARCH_SET_FS
  targets += fsgsbase
endif

include ../../../template/main.mk

ARCH_SET_FS: ARCH_SET_FS.o
fsgsbase: fsgsbase.o
