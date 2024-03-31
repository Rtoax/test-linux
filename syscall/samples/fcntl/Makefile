
TARGETS := F_GET_SEALS
TARGETS += F_ADD_SEALS
TARGETS += F_SETLKW
TARGETS += F_DUPFD
TARGETS += F_GETFD

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
F_GET_SEALS: F_GET_SEALS.o
F_ADD_SEALS: F_ADD_SEALS.o
F_SETLKW: F_SETLKW.o
F_DUPFD: F_DUPFD.o
F_GETFD: F_GETFD.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
