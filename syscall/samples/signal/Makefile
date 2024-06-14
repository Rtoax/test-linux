TARGETS := signal
TARGETS += sigaction sigaction-2 sigaction-3
TARGETS += sigwait
TARGETS += sigaddset
TARGETS += signo
TARGETS += psignal
TARGETS += kill kill-fork killpg
TARGETS += raise
TARGETS += strsignal
TARGETS += alarm-sleep
TARGETS += SIGFPE SIGHUP SIGALRM SIGUSR1 SIGUSR1-1 SIGUSR2 NSIG SIGCHLD SIGRTMAX
TARGETS += sigaltstack

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: sig.h ${TARGETS}
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
SIGFPE: SIGFPE.o
SIGHUP: SIGHUP.o
SIGALRM: SIGALRM.o
SIGUSR1: SIGUSR1.o
SIGUSR1-1: SIGUSR1-1.o
SIGUSR2: SIGUSR2.o
SIGCHLD: SIGCHLD.o
SIGRTMAX: SIGRTMAX.o
NSIG: NSIG.o
strsignal: strsignal.o
alarm-sleep: alarm-sleep.o
sigaltstack: sigaltstack.o

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o sig.h
