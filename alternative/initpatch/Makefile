LDS := ld-alternative.lds

TARGETS :=

ifeq ($(shell uname -m),x86_64)
  TARGETS += main
else
  $(warning Not support arch except x86_64)
endif

CC := gcc

CFLAGS :=
LDFLAGS :=

CFLAGS += -Wl,-T${LDS}
ifneq ($(shell ld --help | grep -o no-warn-rwx-segments),)
  CFLAGS += -Wl,--no-warn-rwx-segments
endif

include ../../template/main.mk

main: main.o
