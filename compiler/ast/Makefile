# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk


CLANG = $(shell which clang 2>/dev/null)

TARGETS :=

ifneq ($(wildcard $(CLANG)),)
  TARGETS += hello
  CC = ${CLANG}
else
  CC := gcc
endif

CFLAGS :=
CFLAGS += -O0

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

%.o: %.c
	@echo -e "  CC/CLANG  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))
	${Q}$(CLANG) -Xclang -ast-dump -fsyntax-only $(<)
	${Q}$(CLANG) -S -emit-llvm $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.ll
