
TARGETS := waitpid
TARGETS += waitpid-sig
TARGETS += waitpid-kill
TARGETS += wait

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
waitpid: waitpid.o
waitpid-sig: waitpid-sig.o
waitpid-kill: waitpid-kill.o
wait: wait.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
