# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


TARGETS :=

CLANG = $(shell which clang 2>/dev/null)
LLVM_CONFIG = $(shell which llvm-config 2>/dev/null)
LLVM_AS = $(shell which llvm-as 2>/dev/null)
LLVM_DIS = $(shell which llvm-dis 2>/dev/null)
LLC = $(shell which llc 2>/dev/null)

ifeq ($(CLANG),)
  $(warning Not found clang, please install clang first)
else
  TARGETS += hello
endif

CC = ${CLANG}

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes

LLVM_CFLAGS :=
LLVM_CXXFLAGS :=

ifeq ($(LLVM_CONFIG),)
  $(warning Not found llvm-config, please install llvm first)
else
  LLVM_CFLAGS += $(shell llvm-config --cflags)
  LLVM_CXXFLAGS += $(shell llvm-config --cxxflags)
endif

CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
hello: hello.o

CFLAGS_hello +=

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S -emit-llvm $(<) -o $(<:.c=.ll)
	${Q}$(LLVM_AS) $(<:.c=.ll) -o $(<:.c=.bc)
	${Q}$(LLVM_DIS) $(<:.c=.bc) -o $(<:.c=.dis.ll)
	${Q}$(LLC) $(<:.c=.ll) -o $(<:.c=.s)
	# TODO: fatal error: 'stdio.h' file not found
	${Q}$(CC) -cc1 -ast-print $(<) || true

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.ll *.s *.bc
