LDS := ld-alternative.lds

targets :=

ifeq ($(shell uname -m),x86_64)
  targets += main
else
  $(warning Not support arch except x86_64)
endif

LDFLAGS += -Wl,-T${LDS}
ifneq ($(shell ld --help | grep -o no-warn-rwx-segments),)
  LDFLAGS += -Wl,--no-warn-rwx-segments
endif

include ../../template/main.mk

main: main.o
