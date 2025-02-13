include ../../../tlbuild.mk


TARGETS :=
ifeq ($(shell uname -m),x86_64)
TARGETS += PTRACE_GETREGS
TARGETS += PTRACE_PEEKDATA
TARGETS += PTRACE_POKEDATA
TARGETS += ptrace-breakpoint
TARGETS += ptrace-breakpoint-2
TARGETS += ptrace-execve
endif
ifeq ($(shell uname -m),aarch64)
endif
TARGETS += PTRACE_GETREGSET
TARGETS += PTRACE_PEEKUSER
TARGETS += PTRACE_PEEKTEXT
TARGETS += PTRACE_SINGLESTEP
TARGETS += peeksiginfo
TARGETS += pthread_create
TARGETS += multi-thread
TARGETS += ptrace-strace


CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: nr.h ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

nr.h: ../nr.sh
	$(shell bash ../nr.sh)
	@cp nr.h ../

# Add more object.o file
PTRACE_GETREGS: PTRACE_GETREGS.o helpers.o
PTRACE_GETREGSET: PTRACE_GETREGSET.o helpers.o
PTRACE_PEEKTEXT: PTRACE_PEEKTEXT.o
PTRACE_PEEKUSER: PTRACE_PEEKUSER.o
PTRACE_PEEKDATA: PTRACE_PEEKDATA.o
PTRACE_POKEDATA: PTRACE_POKEDATA.o
PTRACE_SINGLESTEP: PTRACE_SINGLESTEP.o
peeksiginfo: peeksiginfo.o
ptrace-breakpoint: ptrace-breakpoint.o
ptrace-breakpoint-2: ptrace-breakpoint-2.o
ptrace-strace: ptrace-strace.o helpers.o
ptrace-execve: ptrace-execve.o helpers.o
pthread_create: pthread_create.o
multi-thread: multi-thread.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt nr.h
