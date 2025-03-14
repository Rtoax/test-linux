include ../../tlbuild.mk


TARGETS :=
TARGETS += error
TARGETS += error_print_progname
TARGETS += error_at_line

CC := gcc

CFLAGS :=
LDFLAGS :=

ifdef M32
  CFLAGS += -m32 -DM32=1
  LDFLAGS += -m32
  $(info Compile 32bit ELF)
endif

all: ${TARGETS}

error: error.o
error_print_progname: error_print_progname.o
error_at_line: error_at_line.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f *.o ${TARGETS}
