targets :=
ifeq ($(shell uname -m),x86_64)
  targets += main
endif

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

main: main.o
