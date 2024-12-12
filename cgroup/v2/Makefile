# SPDX-License-Identifier: GPL-3.0
SHELL = /bin/bash

ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

TARGETS :=
TARGETS += mount

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -DDEBUG -O0 -g

LDFLAGS :=

.PHONY: build
build: ${TARGETS}
	@echo -e "  \033[1;33mDone\033[m"

mount: mount.o

CFLAGS_mount := -DTEST_MAIN=1
LDFLAGS_mount :=

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(Q)$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	$(Q)$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	$(Q)sudo umount *.mnt || :
	$(Q)rm -rf ${TARGETS} *.mnt *.o
