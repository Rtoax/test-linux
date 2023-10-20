CC = clang
CFLAGS := -Werror -Wall -pthread
CFLAGS += -DHAVE_MBARRIER=1
CFLAGS += -I$(shell realpath .)/../../../synchronization/barrier/

TARGETS := barrier

build: ${TARGETS}

barrier: barrier.o

clean:
	@rm -f *.o *.d ${TARGETS}
