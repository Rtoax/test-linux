# SPDX-License-Identifier: GPL-3.0
__USE_C_HELPERS__ = y

include helpers.mk
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

target-prep-y := sig.h
target-test-y := test0

sigaddset-objs := ${C_HELPERS}

CFLAGS += -I../../../

LDFLAGS_tkill := -pthread
LDFLAGS_tgkill := -pthread
CFLAGS_tgkill := -DTGKILL=1
CFLAGS_SIGRTMAX := ${sig-cflags}

include main.mk

sig.h:
	$(shell bash signo.sh)

test0: ${target-y}
	$(call log_tgt,TEST,$(@))
	./sigpending &
	sleep 1
	kill -2 $(shell pidof sigpending) # SIGINT
	sleep 1
	kill -20 $(shell pidof sigpending) # SIGTSTP
	sleep 1
	kill -9 $(shell pidof sigpending)
