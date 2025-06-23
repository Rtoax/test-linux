TARGETS :=
TARGETS += rdtsc_user
TARGETS += rdtscp_user
TARGETS += rdtsc_cmp
TARGETS += rdtsc_evil

CFLAGS :=
ARCH_LIB_CPUID :=

CFLAGS += -g -ggdb
CFLAGS += -D_GNU_SOURCE
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
