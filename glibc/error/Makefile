target-y :=
target-y += error
target-y += error_print_progname
target-y += error_at_line

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

include ../../template/main.mk

error: error.o
error_print_progname: error_print_progname.o
error_at_line: error_at_line.o
