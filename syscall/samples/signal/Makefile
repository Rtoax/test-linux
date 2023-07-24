
TARGETS := signal
TARGETS += psignal
TARGETS += kill kill-fork killpg
TARGETS += raise
TARGETS += SIGFPE SIGHUP SIGALRM SIGUSR1 SIGUSR2 NSIG

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../../
CFLAGS += -I../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

signal: signal.o
psignal: psignal.o
raise: raise.o
kill: kill.o
kill-fork: kill-fork.o
killpg: killpg.o
SIGFPE: SIGFPE.o
SIGHUP: SIGHUP.o
SIGALRM: SIGALRM.o
SIGUSR1: SIGUSR1.o
SIGUSR2: SIGUSR2.o
NSIG: NSIG.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
