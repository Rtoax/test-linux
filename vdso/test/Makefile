include ../../template/arch.mk

target-y :=
target-cpp-y :=

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

include ../../template/main.mk

evil-clock-test: evil-clock-test.cpp.o
accuracy: accuracy.o
clock_gettime.sec: clock_gettime.sec.o tsc_freq.o
clock_gettime.nsec: clock_gettime.nsec.o tsc_freq.o
time: time.o
