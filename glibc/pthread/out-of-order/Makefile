CC = clang
CFLAGS := -Werror -Wall -pthread
CFLAGS += -DHAVE_MBARRIER=1

TARGETS := barrier

build: ${TARGETS}

barrier: barrier.o

clean:
	@rm -f *.o *.d ${TARGETS}
