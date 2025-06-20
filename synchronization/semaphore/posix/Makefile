TARGETS := semaphore
TARGETS += latency
TARGETS += pthread-semaphore

CFLAGS := -Werror -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -lpthread

include ../../../template/main.mk

semaphore: semaphore.o
latency: latency.o
pthread-semaphore: pthread-semaphore.o
