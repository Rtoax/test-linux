# Rong Tao, 2022-03-11

TARGETS :=
TARGETS += accuracy
TARGETS += clock_gettime.sec
TARGETS += clock_gettime.nsec

all: ${TARGETS}

ARCH=$(shell uname -m)

CFLAGS := -O2
CFLAGS += -pthread

CXXFLAGS := $(CFLAGS)

ifeq (${ARCH}, x86_64)
	TARGETS += evil-clock-test
	TARGETS += time
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

clean:
	make -C dpdk clean
	rm -f $(TARGETS)
