# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../tlbuild.mk


CC := gcc

include ../../compiler/compiler.mk

TARGETS :=
TARGETS += _GLOBAL_OFFSET_TABLE_
ifeq ($(shell uname -m),x86_64)
  ifeq (${CC_M32},1)
    $(info ${CC} support -m32)
    TARGETS += _GLOBAL_OFFSET_TABLE_-32
  endif
endif

CFLAGS :=
LDFLAGS :=

CFLAGS += -O0 -g -ggdb

ifdef STATIC
  LDFLAGS += -static
endif

# Debian 12 default compile PIE EXEC, Fedora40 default compile no-PIE EXEC.
# Default no-PIE in my case.
ifdef PIE
  # If only -fpic in CFLAGS, 'Illegal instruction (core dumped)' on x86
  CFLAGS += -pie -fPIE -DPIE=1
  LDFLAGS += -pie -fPIE
else
  CFLAGS += -no-pie
  LDFLAGS += -no-pie
endif

CFLAGS__GLOBAL_OFFSET_TABLE_-32 := -m32 -DM32=1
LDFLAGS__GLOBAL_OFFSET_TABLE_-32 := -m32

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

_GLOBAL_OFFSET_TABLE_: _GLOBAL_OFFSET_TABLE_.o
_GLOBAL_OFFSET_TABLE_-32: _GLOBAL_OFFSET_TABLE_-32.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.s *.o *.d
