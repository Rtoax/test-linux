TARGETS :=
ifeq ($(shell uname -m),x86_64)
  TARGETS += ARCH_SET_FS
  TARGETS += fsgsbase
endif

include ../../../template/main.mk

ARCH_SET_FS: ARCH_SET_FS.o
fsgsbase: fsgsbase.o
