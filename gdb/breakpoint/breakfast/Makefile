target-y :=
ifeq ($(shell uname -m),x86_64)
  target-y += tst
endif

CFLAGS := -O0

include ../../../template/main.mk

tst: tst.o breakfast.o
