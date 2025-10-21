sub-dir := breakfast

target-y :=
ifeq ($(shell uname -m),x86_64)
  target-y += int3
else ifeq ($(shell uname -m),aarch64)
  target-y += brk
endif

include ../../template/main.mk

int3: int3.o
brk: brk.o
