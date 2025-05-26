# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

TARGETS :=
TARGETS += overwrite-plt

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE

CFLAGS_overwrite-plt := -DOVERWRITE=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

overwrite-plt: overwrite-plt.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.out
