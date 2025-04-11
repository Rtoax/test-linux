# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

sub-dir := bitmask
sub-dir += bitops
sub-dir += fft
sub-dir += hashmap
sub-dir += linklist
sub-dir += rbtree
sub-dir += md5
sub-dir += math
sub-dir += string
sub-dir += sort
sub-dir += search

include ../template/subdir-header.mk

TARGETS :=
TARGETS += pi

DEBUG ?= yes
CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../macro/

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
endif

.PHONY: build
build: ${TARGETS} $(sub-dir-build)
	@echo -e " \033[1;33m Done \033[m"

pi: pi.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d

include ../template/subdir-footer.mk
