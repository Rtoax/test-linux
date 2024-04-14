TARGETS :=
TARGETS += fallocate
TARGETS += splice splice-read
# F_ flags
TARGETS += F_GET_SEALS
TARGETS += F_ADD_SEALS
TARGETS += F_SETLKW
TARGETS += F_DUPFD
TARGETS += F_GETFD
TARGETS += F_GETFL
# O_ flags
TARGETS += O_CLOEXEC
TARGETS += O_TMPFILE

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
fallocate: fallocate.o
splice: splice.o
splice-read: splice-read.o

F_GET_SEALS: F_GET_SEALS.o
F_ADD_SEALS: F_ADD_SEALS.o
F_SETLKW: F_SETLKW.o
F_DUPFD: F_DUPFD.o
F_GETFD: F_GETFD.o
F_GETFL: F_GETFL.o

O_CLOEXEC: O_CLOEXEC.o
O_TMPFILE: O_TMPFILE.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"
	./fallocate.test.sh
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt *.dat
