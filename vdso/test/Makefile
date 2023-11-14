# Rong Tao, 2022-03-11

TARGETS := clock_gettime.sec
TARGETS += clock_gettime.nsec
TARGETS += evil-clock-test

all: ${TARGETS}

ARCH=$(shell uname -m)

CFLAGS := -O2
CFLAGS += -pthread

ifeq (${ARCH}, x86_64)
LIBS += ./dpdk/tsc_freq.o
MACROS += -DHAVE_DPDK_TSC_FREQ
else
 ifeq (${ARCH}, aarch64)
 LIBS +=
 MACROS +=
 else
 $(error Not support arch.)
 endif
endif

${LIBS}:
	make -C dpdk

clock_gettime.sec: ${LIBS}
	gcc clock_gettime.c ${MACROS} ${LIBS} -o $@ -DACCURATE_TO_SEC
clock_gettime.nsec: ${LIBS}
	gcc clock_gettime.c ${MACROS} ${LIBS} -o $@
evil-clock-test:
	g++ ${CFLAGS} evil-clock-test.cc -o evil-clock-test

clean:
	make -C dpdk clean
	rm -f $(TARGETS)
