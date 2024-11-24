# SPDX-License-Identifier: GPL-3.0
SHELL = bash

TARGETS := hello
TARGETS += hello-pie
TARGETS += is_pie

CC := gcc

CFLAGS :=
LDFLAGS :=

CFLAGS_hello += -no-pie
LDFLAGS_hello += -no-pie
CFLAGS_hello-pie := -fpie
LDFLAGS_hello-pie := -pie
CFLAGS_proc := -fpie
LDFLAGS_is_pie := -lelf

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"
	@$(shell diff -up hello.s hello-pie.s >> build.log)

hello: hello.o libtest-linux-c.a
hello-pie: hello-pie.o libtest-linux-c.a
is_pie: is_pie.o

include ../../../libs/libs.mk

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	@$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))
	@size --format=sysv $(@) >> build.log

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.s *.o *.d *.log *.a
