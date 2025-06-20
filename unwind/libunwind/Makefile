TARGETS :=
TARGETS_CPP :=

TARGETS += tst
TARGETS += unw_regname
TARGETS += unw_create_addr_space
TARGETS += do_backtrace
TARGETS += unwind-backtrace

TARGETS_CPP += backtrace-pid
ifeq ($(shell uname -m),x86_64)
  TARGETS += backtrace
endif

UNWIND_PTRACE :=
UNWIND_PTRACE1 := /lib64/libunwind-ptrace.a
UNWIND_PTRACE2 := /usr/lib/$(shell uname -m)-linux-gnu/libunwind-ptrace.a

LDFLAGS += -lunwind
LDFLAGS += -lunwind-$(shell uname -m)

ifneq ($(wildcard $(UNWIND_PTRACE1)),)
  UNWIND_PTRACE := ${UNWIND_PTRACE1}
endif
ifneq ($(wildcard $(UNWIND_PTRACE2)),)
  UNWIND_PTRACE := ${UNWIND_PTRACE2}
  # Fix: undefined reference to symbol 'lzma_stream_buffer_decode@@XZ_5.0'
  # on Debian 12 x86_64
  CFLAGS += -llzma -no-pie
endif
ifeq (${UNWIND_PTRACE},)
  $(error Not found libunwind-ptrace.a)
endif

CFLAGS_tst := -g -ggdb -O0

include ../../template/main.mk

tst: tst.o
unw_regname: unw_regname.o
unw_create_addr_space: unw_create_addr_space.o
backtrace: backtrace.o
backtrace-pid: backtrace-pid.opp
do_backtrace: do_backtrace.o
unwind-backtrace: unwind-backtrace.o
