SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


CACHEFLUSH_HDR = /usr/include/asm/cacheflush.h

TARGETS :=
ifneq ($(wildcard $(CACHEFLUSH_HDR)),)
ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
TARGETS += cacheflush
endif
endif

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

cacheflush: cacheflush.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o

