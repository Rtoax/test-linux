TARGETS :=
ifeq ($(shell uname -m),x86_64)
  TARGETS += tst
endif

CFLAGS := -O0

include ../../../template/main.mk

tst: tst.o breakfast.o
