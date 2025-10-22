# SPDX-License-Identifier: GPL-3.0
include signal.mk

subdir-y := SIGURG

target-y := signal
target-y += sigaction sigaction-2 sigaction-3
target-y += sigwait
target-y += sigaddset
target-y += signo
target-y += psignal
target-y += kill tkill tgkill kill-fork killpg
target-y += raise
target-y += strsignal
target-y += alarm alarm-sleep alarm-sleep-2
target-y += SIGFPE SIGHUP SIGALRM SIGUSR1 SIGUSR1-1 SIGUSR2 NSIG SIGCHLD SIGRTMAX
target-y += SIGPIPE SIGBUS SIGILL
target-y += SIGTERM SIGKILL
target-y += sigaltstack
target-y += sigpending
target-y += sigsuspend
target-y += sigprocmask
target-y += signalfd

CFLAGS += -I../../../

LDFLAGS_tkill := -pthread
LDFLAGS_tgkill := -pthread
CFLAGS_tgkill := -DTGKILL=1
CFLAGS_SIGRTMAX := ${SIGRT_CFLAGS}

target-prep-y := sig.h
target-test-y := test0

include ../../../template/main.mk

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
tkill: tkill.o
tgkill: tgkill.o
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
SIGILL: SIGILL.o
SIGTERM: SIGTERM.o
SIGKILL: SIGKILL.o
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


test0: ${target-y}
	$(call log_tgt_exe,TEST,,$(@))
	./sigpending &
	sleep 1
	kill -2 $(shell pidof sigpending) # SIGINT
	sleep 1
	kill -20 $(shell pidof sigpending) # SIGTSTP
	sleep 1
	kill -9 $(shell pidof sigpending)
