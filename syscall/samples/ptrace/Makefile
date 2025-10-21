target-y :=
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

CFLAGS :=
CFLAGS += -pthread

target-prep-y := nr.h

include ../../../template/main.mk

nr.h: ../nr.sh
	$(shell bash ../nr.sh)
	${Q}cp nr.h ../

PTRACE_GETREGS: PTRACE_GETREGS.o ptrace_helpers.o
PTRACE_GETREGSET: PTRACE_GETREGSET.o ptrace_helpers.o
PTRACE_PEEKTEXT: PTRACE_PEEKTEXT.o
PTRACE_PEEKUSER: PTRACE_PEEKUSER.o
PTRACE_PEEKDATA: PTRACE_PEEKDATA.o
PTRACE_POKEDATA: PTRACE_POKEDATA.o
PTRACE_SINGLESTEP: PTRACE_SINGLESTEP.o
peeksiginfo: peeksiginfo.o
ptrace-breakpoint: ptrace-breakpoint.o
ptrace-breakpoint-2: ptrace-breakpoint-2.o
ptrace-strace: ptrace-strace.o ptrace_helpers.o
ptrace-execve: ptrace-execve.o ptrace_helpers.o
pthread_create: pthread_create.o
multi-thread: multi-thread.o
