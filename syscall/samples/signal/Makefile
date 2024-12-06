sub-dir := SIGURG

TARGETS := signal
TARGETS += sigaction sigaction-2 sigaction-3
TARGETS += sigwait
TARGETS += sigaddset
TARGETS += signo
TARGETS += psignal
TARGETS += kill kill-fork killpg
TARGETS += raise
TARGETS += strsignal
TARGETS += alarm alarm-sleep alarm-sleep-2
TARGETS += SIGFPE SIGHUP SIGALRM SIGUSR1 SIGUSR1-1 SIGUSR2 NSIG SIGCHLD SIGRTMAX SIGPIPE SIGBUS
TARGETS += sigaltstack
TARGETS += sigpending
TARGETS += sigsuspend
TARGETS += sigprocmask
TARGETS += signalfd

CC = gcc
SHELL = /bin/bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g


sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: sig.h ${TARGETS} $(sub-dir-build)
	@echo
	@echo -e " \033[1;33m Done \033[m"

sig.h:
	$(shell bash signo.sh)

signo: signo.o
signal: signal.o
sigaction: sigaction.o
sigaction-2: sigaction-2.o
sigaction-3: sigaction-3.o
sigwait: sigwait.o
sigaddset: sigaddset.o
psignal: psignal.o
raise: raise.o
kill: kill.o
kill-fork: kill-fork.o
killpg: killpg.o
SIGBUS: SIGBUS.o
SIGFPE: SIGFPE.o
SIGHUP: SIGHUP.o
SIGALRM: SIGALRM.o
SIGUSR1: SIGUSR1.o
SIGUSR1-1: SIGUSR1-1.o
SIGUSR2: SIGUSR2.o
SIGCHLD: SIGCHLD.o
SIGRTMAX: SIGRTMAX.o
SIGPIPE: SIGPIPE.o
NSIG: NSIG.o
strsignal: strsignal.o
alarm: alarm.o
alarm-sleep: alarm-sleep.o
alarm-sleep-2: alarm-sleep-2.o
sigaltstack: sigaltstack.o
sigpending: sigpending.o
sigsuspend: sigsuspend.o
sigprocmask: sigprocmask.o
signalfd: signalfd.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(<)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32msigpending\033[m"
	./sigpending &
	sleep 1
	kill -2 $(shell pidof sigpending) # SIGINT
	sleep 1
	kill -20 $(shell pidof sigpending) # SIGTSTP
	sleep 1
	kill -9 $(shell pidof sigpending)

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o sig.h

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean

