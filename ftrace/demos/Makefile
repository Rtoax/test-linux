# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

include ../../compiler/compiler.mk

CC := gcc

TARGETS := main
TARGETS += main-pg
# FIXME: aarch64 seems like don't support -mfentry
ifeq ($(CC_-mfentry),1)
  TARGETS += main-pg-fentry
endif

CFLAGS := -Werror -Wall -O0

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

main: main.o-no-pg foo.o-pg
main-pg: main-pg.o-pg foo.o-no-pg
main-pg-fentry: main-pg-fentry.o-pg-fentry foo.o-pg-fentry

%.o-no-pg: %.c
	@echo -e "  CC NO-PG \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS)

%.o-pg: %.c
	@echo -e "  CC PG  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -pg

%.o-pg-fentry: %.c
	@echo -e "  CC PG FENTRY  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*)) -pg -mfentry

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.o-pg *.o-no-pg *.o-pg-fentry
