# Rong Tao, 2022-03-11
include ../../tlbuild.mk

TARGETS :=
TARGETS += accuracy
TARGETS += clock_gettime.sec
TARGETS += clock_gettime.nsec

CC = gcc

all: ${TARGETS}

ARCH=$(shell uname -m)

DPDK_TSC_FREQ :=

CFLAGS := -O2
CFLAGS += -pthread

CXXFLAGS := $(CFLAGS)

ifeq (${ARCH},x86_64)
  TARGETS += evil-clock-test
  TARGETS += time
  DPDK_TSC_FREQ = ./dpdk/tsc_freq.o
endif

accuracy: accuracy.o
clock_gettime.sec: clock_gettime.sec.o ${DPDK_TSC_FREQ}
clock_gettime.nsec: clock_gettime.nsec.o ${DPDK_TSC_FREQ}
time: time.o
evil-clock-test: evil-clock-test.o

./dpdk/tsc_freq.o:
	${Q}make -C dpdk

CFLAGS_clock_gettime.sec := -DHAVE_DPDK_TSC_FREQ -DACCURATE_TO_SEC
CFLAGS_clock_gettime.nsec := -DHAVE_DPDK_TSC_FREQ

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	${Q}make -C dpdk clean
	${Q}rm -f $(TARGETS) *.o
