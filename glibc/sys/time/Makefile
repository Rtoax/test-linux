TARGETS :=
TARGETS += adjtime
TARGETS += TIMEVAL_TO_TIMESPEC

CFLAGS := -Werror -Wall
CFLAGS += -D_GNU_SOURCE

include ../../../template/main.mk

adjtime: adjtime.o
TIMEVAL_TO_TIMESPEC: TIMEVAL_TO_TIMESPEC.o
