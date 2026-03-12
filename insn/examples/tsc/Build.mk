__USE_PTHREAD_HELPERS__ = y

include helpers.mk

target-y += rdtsc_user
target-y += rdtscp_user
target-y += rdtsc_cmp
target-y += rdtsc_evil

rdtsc_evil-objs := ${PTHREAD_HELPERS}

CFLAGS += -g -ggdb
CFLAGS += -pthread
CFLAGS += -O3
