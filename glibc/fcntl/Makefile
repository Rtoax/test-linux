TARGETS :=
TARGETS += posix_fallocate

CFLAGS :=

CFLAGS += -D_GNU_SOURCE=1

all: ${TARGETS}

posix_fallocate: posix_fallocate.o

clean:
	rm -f ${TARGETS} *.o *.txt
