targets :=
targets-cpp :=

targets += accuracy
targets += clock_gettime.sec
targets += clock_gettime.nsec

ARCH := $(shell uname -m)

ifeq (${ARCH},x86_64)
  targets-cpp += evil-clock-test
  targets += time
endif

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
