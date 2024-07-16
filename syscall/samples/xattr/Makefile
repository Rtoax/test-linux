SHELL = bash


TARGETS :=
TARGETS += setxattr
TARGETS += demo-1

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@touch a.txt
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
setxattr: setxattr.o
demo-1: demo-1.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
