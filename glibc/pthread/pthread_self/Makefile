CC = clang
CFLAGS := -Werror -Wall -pthread

TARGETS := pthread_self

build: ${TARGETS}

pthread_self: pthread_self.o

clean:
	@rm -f *.o *.d ${TARGETS}
