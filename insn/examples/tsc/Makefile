targets :=
targets += rdtsc_user
targets += rdtscp_user
targets += rdtsc_cmp
targets += rdtsc_evil

CFLAGS :=
ARCH_LIB_CPUID :=

CFLAGS += -g -ggdb
CFLAGS += -pthread
CFLAGS += -O3
ifdef STATIC
  CFLAGS += -static
  $(info Defined STATIC)
endif

include ../../../template/main.mk

pthread_helpers.o: pthread_helpers.h
rdtsc_user: rdtsc_user.o
rdtscp_user: rdtscp_user.o
rdtsc_cmp: rdtsc_cmp.o
rdtsc_evil: rdtsc_evil.o pthread_helpers.o
