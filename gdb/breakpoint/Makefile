sub-dir := breakfast

TARGETS :=
ifeq ($(shell uname -m),x86_64)
  TARGETS += int3
else ifeq ($(shell uname -m),aarch64)
  TARGETS += brk
endif

include ../../template/main.mk

int3: int3.o
brk: brk.o
