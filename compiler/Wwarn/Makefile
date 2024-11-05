SHELL = bash

TARGETS :=
TARGETS += duplicate-decl-specifier
TARGETS += no-warn
TARGETS += no-error

CC = gcc

CFLAGS :=

CFLAGS_duplicate-decl-specifier := -Wall -Wduplicate-decl-specifier
CFLAGS_no-warn := -Wno-warn
CFLAGS_no-error := -Wno-error

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

duplicate-decl-specifier: duplicate-decl-specifier.o
no-warn: no-warn.o
no-error: no-error.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	@$(CC) $(CFLAGS) -S $(<) -o $(<:.c=-nof.s) -Wno-error

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
