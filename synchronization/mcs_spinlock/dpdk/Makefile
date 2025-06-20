TARGETS :=
ifeq ($(shell uname -m),x86_64)
  TARGETS += main
endif

CFLAGS := -Werror -Wall
CFLAGS += -pthread

include ../../../template/main.mk

main: main.o
