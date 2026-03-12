target-y += tst
target-y += unw_regname
target-y += unw_create_addr_space
target-y += do_backtrace
target-y += unwind-backtrace
target-${IS_X86_64} += backtrace

target-cpp-y += backtrace-pid

UNWIND_PTRACE1 := /lib64/libunwind-ptrace.a
UNWIND_PTRACE2 := /usr/lib/$(shell uname -m)-linux-gnu/libunwind-ptrace.a

LDFLAGS += -lunwind
LDFLAGS += -lunwind-ptrace
LDFLAGS += -lunwind-$(shell uname -m)
LDXXFLAGS := ${LDFLAGS}

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

CFLAGS += -Wno-error=nonnull
CXXFLAGS += -Wno-error=nonnull

CFLAGS_tst := -g -ggdb -O0
