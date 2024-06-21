
TARGETS :=
TARGETS_CPP :=

TARGETS += test
TARGETS += unw_regname
TARGETS += unw_create_addr_space
TARGETS += do_backtrace
TARGETS += unwind-backtrace

TARGETS_CPP += backtrace-pid
ifeq ($(shell uname -m),x86_64)
TARGETS += backtrace
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc
CXX = g++

CFLAGS :=
CFLAGS += -lunwind
ifeq ($(shell uname -m),x86_64)
CFLAGS += -lunwind-x86_64
endif
ifeq ($(shell uname -m),aarch64)
CFLAGS += -lunwind-aarch64
endif

UNWIND_PTRACE=/lib64/libunwind-ptrace.a

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS} ${TARGETS_CPP}
	@echo -e " \033[1;33m Done \033[m"

CFLAGS_test := -g -ggdb -O0

test: test.o
unw_regname: unw_regname.o
unw_create_addr_space: unw_create_addr_space.o
backtrace: backtrace.o
backtrace-pid: backtrace-pid.oo
do_backtrace: do_backtrace.o
unwind-backtrace: unwind-backtrace.o

%.o: %.c
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

%.oo: %.cc
	@echo -e "CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CXX) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

${TARGETS}: %:
	@echo -e "CC  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(<) ${UNWIND_PTRACE}

${TARGETS_CPP}: %:
	@echo -e "CC  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	$(CXX) $(CFLAGS) -o $(@) $(<) ${UNWIND_PTRACE}

clean:
	rm -f ${TARGETS} ${TARGETS_CPP} *.o *.oo
