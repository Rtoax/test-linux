
TARGETS= \
	backtrace.out \
	backtrace2.out \
	do_backtrace.out

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -lunwind -lunwind-ptrace -lunwind-generic

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.out: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1;31m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(<)

clean:
	rm -f ${TARGETS} *.o *.d
