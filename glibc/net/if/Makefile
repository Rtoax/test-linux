# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


TARGETS :=
TARGETS += if_indextoname
TARGETS += if_nametoindex
TARGETS += if_nameindex

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LDFLAGS :=


.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

if_indextoname: if_indextoname.o
if_nametoindex: if_nametoindex.o
if_nameindex: if_nameindex.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
