# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

include ../../compiler.mk

CC := gcc
CFLAGS :=
# Compile to dynamic library.
CFLAGS_PIC := -fPIC
LDFLAGS :=

TARGETS :=
TARGETS_SO :=

TARGETS += main
ifeq ($(CC_-mfentry),1)
  TARGETS += fentry
endif

TARGETS_SO += libmcount-nop.so
TARGETS_SO += libconstructor-obj.so

CFLAGS_main := -pg
CFLAGS_fentry := -pg -mfentry
CFLAGS_mcount-nop := ${CFLAGS_PIC}
CFLAGS_constructor-obj := ${CFLAGS_PIC}

.PHONY: all
all: ${TARGETS} ${TARGETS_SO}
	@echo -e " \033[1;33m Done \033[m"

main: main.o
fentry: fentry.o
libmcount-nop.so: mcount-nop.o
libconstructor-obj.so: constructor-obj.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

$(TARGETS_SO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) -shared -fPIC $(LDFLAGS) $(LDFLAGS_$(*))

.PHONY: test
test: ${TARGETS} ${TARGETS_SO}
	$(Q)LD_PRELOAD=./libmcount-nop.so ./main
	$(Q)LD_PRELOAD=./libmcount-nop.so ./fentry
	$(Q)LD_PRELOAD=./libconstructor-obj.so ./main

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_SO)\033[m"
	@echo -e "  CLEAN"
	$(Q)rm -f ${TARGETS} ${TARGETS_SO} *.o *.out
