TARGETS :=
TARGETS += bfd_init
TARGETS += bfd_symbol_info
TARGETS += breakpoint_tst breakpoint_bfd
TARGETS += reloc

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lbfd

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

bfd_init: bfd_init.o
bfd_symbol_info: bfd_symbol_info.o
breakpoint_tst: breakpoint_tst.o
breakpoint_bfd: breakpoint_bfd.o
reloc: reloc.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d *.out *.s

