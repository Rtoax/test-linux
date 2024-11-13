# SPDX-License-Identifier: GPL-3.0
SHELL = bash

TARGETS := list_test

list_test: list_test.o list.o llist.o

CC = gcc

CFLAGS :=
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^)

test: ${TARGETS}
	./list_test >/dev/null

clean:
	@echo -e "  TARGETS  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d
