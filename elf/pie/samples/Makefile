# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../../elf.mk

TARGETS := hello
TARGETS += hello-pie
TARGETS += is_pie

CC := gcc
LIBS_DIR := ../../../libs/

CFLAGS :=
LDFLAGS :=

CFLAGS += -I${LIBS_DIR}

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

include ${LIBS_DIR}/libs.mk

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CC) -S $(<) -o $(<:.c=.s) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))
	@size --format=sysv $(@) >> build.log
	$(Q)echo "  $(@) : $(call elf_is_pie,${@})"

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.d *.log *.a
