# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

TARGETS :=
TARGETS += swapcontext
TARGETS += getcontext
TARGETS += setcontext
TARGETS += ucontext_t
TARGETS += makecontext
TARGETS += demo1

CC := gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

CFLAGS_setcontext := -DTEST_SETCONTEXT=1

.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

swapcontext: swapcontext.o
getcontext: getcontext.o
setcontext: setcontext.o
ucontext_t: ucontext_t.o
makecontext: makecontext.o
demo1: demo1.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

.PHONY: test
test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

.PHONY: clean
clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.log
	${Q}rm -rf tmpd-* tmp-*
