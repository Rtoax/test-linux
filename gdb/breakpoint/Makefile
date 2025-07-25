sub-dir := breakfast

targets :=
ifeq ($(shell uname -m),x86_64)
  targets += int3
else ifeq ($(shell uname -m),aarch64)
  targets += brk
endif

include ../../template/main.mk

int3: int3.o
brk: brk.o
