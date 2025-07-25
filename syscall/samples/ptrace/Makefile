targets :=
ifeq ($(shell uname -m),x86_64)
  targets += PTRACE_GETREGS
  targets += PTRACE_PEEKDATA
  targets += PTRACE_POKEDATA
  targets += ptrace-breakpoint
  targets += ptrace-breakpoint-2
  targets += ptrace-execve
else ifeq ($(shell uname -m),aarch64)
endif
targets += PTRACE_GETREGSET
targets += PTRACE_PEEKUSER
targets += PTRACE_PEEKTEXT
targets += PTRACE_SINGLESTEP
targets += peeksiginfo
targets += pthread_create
targets += multi-thread
targets += ptrace-strace

CFLAGS :=
CFLAGS += -pthread

targets-prep := nr.h

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
