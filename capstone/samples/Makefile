# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../tlbuild.mk


CS_HDR_CAPSTONE = /usr/include/capstone/capstone.h

TARGETS :=
TARGETS += version
TARGETS += simple
TARGETS += detail

ifeq ($(wildcard $(CS_HDR_CAPSTONE)),)
  TARGETS :=
  $(warning "WARNING: You need to install capstone development")
endif

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -DDEBUG -O0 -g
CFLAGS += -lcapstone

LDFLAGS := -lcapstone


build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

version: version.o
detail: detail.o
simple: simple.o

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
	${Q}rm -f ${TARGETS} *.o
