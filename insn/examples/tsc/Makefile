__USE_PTHREAD_HELPERS__ := 1

target-y :=
target-y += rdtsc_user
target-y += rdtscp_user
target-y += rdtsc_cmp
target-y += rdtsc_evil

CFLAGS :=
CFLAGS += -g -ggdb
CFLAGS += -pthread
CFLAGS += -O3

include ../../../template/main.mk

pthread_helpers.o: pthread_helpers.h
rdtsc_user: rdtsc_user.o
rdtscp_user: rdtscp_user.o
rdtsc_cmp: rdtsc_cmp.o
rdtsc_evil: rdtsc_evil.o ${PTHREAD_HELPERS}
