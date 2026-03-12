target-y += accuracy
target-${IS_X86_64} += clock_gettime.sec
target-${IS_X86_64} += clock_gettime.nsec

target-cpp-${IS_X86_64} += evil-clock-test
target-${IS_X86_64} += time

clock_gettime.sec-objs := tsc_freq.o
clock_gettime.nsec-objs := tsc_freq.o

CFLAGS := -O2
CFLAGS += -pthread
CFLAGS += -Idpdk
CXXFLAGS := $(CFLAGS)

CFLAGS_clock_gettime.sec := -DHAVE_DPDK_TSC_FREQ -DACCURATE_TO_SEC
CFLAGS_clock_gettime.nsec := -DHAVE_DPDK_TSC_FREQ
