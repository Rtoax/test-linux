targets :=
ifeq ($(shell uname -m),x86_64)
  targets += tst
endif

CFLAGS := -O0

include ../../../template/main.mk

tst: tst.o breakfast.o
