# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk

TARGETS :=
TARGETS += fork vfork fork-share
TARGETS += fork-ENOMEM fork-ENOMEM-2
TARGETS += fork_twice

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE -D__USE_GNU
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

CFLAGS_vfork := -DVFORK=1

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

helpers.o: helpers.h

fork: fork.o
vfork: vfork.o
fork_twice: fork_twice.o
fork-share: fork-share.o
fork-ENOMEM: fork-ENOMEM.o helpers.o
fork-ENOMEM-2: fork-ENOMEM-2.o helpers.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.pid

