# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS := main
TARGETS += main-pg

CC = gcc

CFLAGS := -Werror -Wall -O0

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

main: main.o-no-pg foo.o-pg
main-pg: main-pg.o-pg foo.o-no-pg

%.o-no-pg: %.c
	@echo -e "  CC NO-PG \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS)

%.o-pg: %.c
	@echo -e "  CC PG  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -pg

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.o-pg *.o-no-pg
