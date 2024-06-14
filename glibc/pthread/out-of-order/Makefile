TARGETS :=
TARGETS += barrier

CC = gcc

CFLAGS := -Werror -Wall -pthread
CFLAGS += -DHAVE_MBARRIER=1
CFLAGS += -I$(shell realpath .)/../../../synchronization/barrier/


build: ${TARGETS}

barrier: barrier.o

clean:
	@rm -f *.o *.d ${TARGETS}
