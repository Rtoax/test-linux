ifeq ($(shell uname -m),x86_64)
  target-y += PTRACE_GETREGS
  target-y += PTRACE_PEEKDATA
  target-y += PTRACE_POKEDATA
  target-y += ptrace-breakpoint
  target-y += ptrace-breakpoint-2
  target-y += ptrace-execve
else ifeq ($(shell uname -m),aarch64)
endif
target-y += PTRACE_GETREGSET
target-y += PTRACE_PEEKUSER
target-y += PTRACE_PEEKTEXT
target-y += PTRACE_SINGLESTEP
target-y += peeksiginfo
target-y += pthread_create
target-y += multi-thread
target-y += ptrace-strace

PTRACE_GETREGS-objs := ptrace_helpers.o
PTRACE_GETREGSET-objs := ptrace_helpers.o
ptrace-strace-objs := ptrace_helpers.o
ptrace-execve-objs := ptrace_helpers.o

CFLAGS += -pthread

target-prep-y := nr.h

include main.mk

nr.h: ../nr.sh
	$(shell bash ../nr.sh)
	${Q}cp nr.h ../
