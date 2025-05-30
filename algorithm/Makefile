# SPDX-License-Identifier: GPL-3.0
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


TARGETS :=
TARGETS += pi

DEBUG ?= yes
CC := gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../macro/

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g -ggdb
endif

include ../template/subdir-pure.mk

pi: pi.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS} $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
