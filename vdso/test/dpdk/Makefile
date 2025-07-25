targets :=
ifeq ($(shell uname -m), x86_64)
  targets += tsc_freq_arch tsc_freq
endif

CFLAGS := -DTEST=1

include ../../../template/main.mk

tsc_freq_arch: tsc_freq_arch.o
tsc_freq: tsc_freq.o
