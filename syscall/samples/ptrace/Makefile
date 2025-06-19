TARGETS :=
ifeq ($(shell uname -m),x86_64)
  TARGETS += PTRACE_GETREGS
  TARGETS += PTRACE_PEEKDATA
  TARGETS += PTRACE_POKEDATA
  TARGETS += ptrace-breakpoint
  TARGETS += ptrace-breakpoint-2
  TARGETS += ptrace-execve
else ifeq ($(shell uname -m),aarch64)
endif
TARGETS += PTRACE_GETREGSET
TARGETS += PTRACE_PEEKUSER
TARGETS += PTRACE_PEEKTEXT
TARGETS += PTRACE_SINGLESTEP
TARGETS += peeksiginfo
TARGETS += pthread_create
TARGETS += multi-thread
TARGETS += ptrace-strace

CFLAGS := -Werror -Wall
CFLAGS += -pthread

TARGETS_PREP := nr.h

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
