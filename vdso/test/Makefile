# Rong Tao, 2022-03-11

all: clock_gettime.sec.out clock_gettime.nsec.out

ARCH=$(shell uname -m)

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

clock_gettime.sec.out: ${LIBS}
	gcc clock_gettime.c ${MACROS} ${LIBS} -o $@ -DACCURATE_TO_SEC
clock_gettime.nsec.out: ${LIBS}
	gcc clock_gettime.c ${MACROS} ${LIBS} -o $@

clean:
	make -C dpdk clean
	rm -f *.out
