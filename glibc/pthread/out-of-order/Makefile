# SPDX-License-Identifier: GPL-3.0
SHELL = bash

TARGETS :=
TARGETS += barrier
TARGETS += no-barrier

CC = gcc

CFLAGS := -Werror -Wall -pthread
CFLAGS += -I$(shell realpath .)/../../../synchronization/barrier/

CFLAGS_barrier += -DHAVE_MBARRIER=1

build: ${TARGETS}

barrier: barrier.o
no-barrier: no-barrier.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f *.o ${TARGETS}
