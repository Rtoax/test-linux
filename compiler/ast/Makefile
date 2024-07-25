SHELL = bash

CLANG = $(shell which clang 2>/dev/null)

TARGETS :=

ifneq ($(wildcard $(CLANG)),)
TARGETS += hello
CC = ${CLANG}
else
CC = gcc
endif

CFLAGS := -Werror -Wall
CFLAGS += -O0

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

hello: hello.o

%.o: %.c
	@echo -e "  CC/CLANG  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	@$(CLANG) -Xclang -ast-dump -fsyntax-only $(<)
	@$(CLANG) -S -emit-llvm $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.ll
