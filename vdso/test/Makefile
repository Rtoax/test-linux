include arch.mk

target-y += accuracy
target-${IS_X86_64} += clock_gettime.sec
target-${IS_X86_64} += clock_gettime.nsec

target-cpp-${IS_X86_64} += evil-clock-test
target-${IS_X86_64} += time

CFLAGS := -O2
CFLAGS += -pthread
CFLAGS += -Idpdk
CXXFLAGS := $(CFLAGS)

CFLAGS_clock_gettime.sec := -DHAVE_DPDK_TSC_FREQ -DACCURATE_TO_SEC
CFLAGS_clock_gettime.nsec := -DHAVE_DPDK_TSC_FREQ

include main.mk

clock_gettime.sec: tsc_freq.o
clock_gettime.nsec: tsc_freq.o
