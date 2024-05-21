TARGETS :=

# FIXME: support sw64
ifneq ($(shell uname -m),sw_64)
TARGETS += barrier
endif

CC = gcc

CFLAGS := -Werror -Wall -pthread
CFLAGS += -DHAVE_MBARRIER=1
CFLAGS += -I$(shell realpath .)/../../../synchronization/barrier/


build: ${TARGETS}

barrier: barrier.o

clean:
	@rm -f *.o *.d ${TARGETS}
