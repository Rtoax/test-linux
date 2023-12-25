
TARGETS :=
ifneq ($(shell uname -m),aarch64)
TARGETS += PTRACE_GETREGS
endif
TARGETS += PTRACE_PEEKTEXT
TARGETS += PTRACE_PEEKUSER
TARGETS += PTRACE_PEEKDATA
TARGETS += PTRACE_POKEDATA
TARGETS += PTRACE_SINGLESTEP
TARGETS += peeksiginfo
TARGETS += ptrace-breakpoint
TARGETS += ptrace-breakpoint-2
TARGETS += ptrace-strace


DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -pthread
CFLAGS += -I../../../
#CFLAGS += -I../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: nr.h ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

nr.h: ../nr.sh
	$(shell sh ../nr.sh)

# Add more object.o file
PTRACE_GETREGS: PTRACE_GETREGS.o helpers.o
PTRACE_PEEKTEXT: PTRACE_PEEKTEXT.o
PTRACE_PEEKUSER: PTRACE_PEEKUSER.o
PTRACE_PEEKDATA: PTRACE_PEEKDATA.o
PTRACE_POKEDATA: PTRACE_POKEDATA.o
PTRACE_SINGLESTEP: PTRACE_SINGLESTEP.o
peeksiginfo: peeksiginfo.o
ptrace-breakpoint: ptrace-breakpoint.o
ptrace-breakpoint-2: ptrace-breakpoint-2.o
ptrace-strace: ptrace-strace.o helpers.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt nr.h
