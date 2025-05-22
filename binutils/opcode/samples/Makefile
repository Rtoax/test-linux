# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk

TARGETS :=
TARGETS += disassemble_init_for_target

CC := gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -DDEBUG -O0
CFLAGS += -Wno-unused-label
CFLAGS += -Wno-unused-variable
CFLAGS += -lopcodes -lbfd

include ../../../elf/pie.mk
include ../../binutils.mk

CFLAGS += -DBINUTILS_VERSION_MAJOR=${BINUTILS_VERSION_MAJOR}
CFLAGS += -DBINUTILS_VERSION_MINOR=${BINUTILS_VERSION_MINOR}

CFLAGS_disassemble_init_for_target := -DARCH_aarch64=1

ifdef DEBUG
  $(info CFLAGS=${CFLAGS})
  $(info LDFLAGS=${LDFLAGS})
endif

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

disassemble_init_for_target: disassemble_init_for_target.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.out
