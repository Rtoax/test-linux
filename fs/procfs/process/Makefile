# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

CC := gcc

CFLAGS :=

TARGETS :=
TARGETS += cmdline
TARGETS += environ
TARGETS += exe
TARGETS += loginuid
TARGETS += pagemap
TARGETS += mem
TARGETS += maps

all: $(TARGETS)

CFLAGS_pagemap := -DHAVE_MAIN=1
CFLAGS_pagemap += -lnuma

cmdline: cmdline.o
environ: environ.o
exe: exe.o
loginuid: loginuid.o
pagemap: pagemap.o
mem: mem.o
maps: maps.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.so

