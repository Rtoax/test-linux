
TARGETS :=
TARGETS += PTRACE_GETREGS
TARGETS += ptrace-breakpoint
TARGETS += ptrace-strace


DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
PTRACE_GETREGS: PTRACE_GETREGS.o helpers.o
ptrace-breakpoint: ptrace-breakpoint.o
ptrace-strace: ptrace-strace.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
