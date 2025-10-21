target-y :=
ifeq ($(shell uname -m),x86_64)
  target-y += main
endif

CFLAGS :=
CFLAGS += -pthread

include ../../../template/main.mk

main: main.o
