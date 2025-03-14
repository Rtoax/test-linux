# SPDX-License-Identifier: GPL-3.0
include ../../../../tlbuild.mk


TARGETS :=
TARGETS += madvise-MADV_MERGEABLE
TARGETS += madvise-MADV_HUGEPAGE

CC := gcc
CXX = g++

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -Wstrict-prototypes
CFLAGS += -pthread
CFLAGS += -O0

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

madvise-MADV_MERGEABLE: madvise-MADV_MERGEABLE.o
madvise-MADV_HUGEPAGE: madvise-MADV_HUGEPAGE.o

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
	${Q}rm -f ${TARGETS} *.o *.dat

