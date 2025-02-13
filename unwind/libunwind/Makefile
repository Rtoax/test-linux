include ../../tlbuild.mk


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
CC = gcc
CXX = g++

UNWIND_PTRACE :=
UNWIND_PTRACE1 := /lib64/libunwind-ptrace.a
UNWIND_PTRACE2 :=

CFLAGS :=
CFLAGS += -lunwind
ifeq ($(shell uname -m),x86_64)
  CFLAGS += -lunwind-x86_64
  UNWIND_PTRACE2 = /usr/lib/x86_64-linux-gnu/libunwind-ptrace.a
endif
ifeq ($(shell uname -m),aarch64)
  CFLAGS += -lunwind-aarch64
  UNWIND_PTRACE2 = /usr/lib/aarch64-linux-gnu/libunwind-ptrace.a
endif

ifneq ($(wildcard $(UNWIND_PTRACE1)),)
  UNWIND_PTRACE=${UNWIND_PTRACE1}
endif
ifneq ($(wildcard $(UNWIND_PTRACE2)),)
  UNWIND_PTRACE=${UNWIND_PTRACE2}
  # Fix: undefined reference to symbol 'lzma_stream_buffer_decode@@XZ_5.0'
  # on Debian 12 x86_64
  CFLAGS += -llzma -no-pie
endif
ifeq (${UNWIND_PTRACE},)
  $(error Not found libunwind-ptrace.a)
endif

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
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.oo: %.cc
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CXX) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${TARGETS}: %:
	@echo -e "  LD  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(<) ${UNWIND_PTRACE} $(CFLAGS) $(CFLAGS_$(*))

${TARGETS_CPP}: %:
	@echo -e "  LD  \033[1m$(<)\033[m to \033[1;32m$(@)\033[m"
	${Q}$(CXX) -o $(@) $(<) ${UNWIND_PTRACE} $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1m$(TARGETS) ${TARGETS_CPP}\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_CPP} *.o *.oo
