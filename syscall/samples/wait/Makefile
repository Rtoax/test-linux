SHELL = bash
include ../../../tlbuild.mk


TARGETS :=
TARGETS += waitpid
TARGETS += waitpid-sig
TARGETS += waitpid-kill
TARGETS += waitpid-status
TARGETS += wait

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
waitpid: waitpid.o
waitpid-sig: waitpid-sig.o
waitpid-kill: waitpid-kill.o
waitpid-status: waitpid-status.o
wait: wait.o

CFLAGS_waitpid-status := -DTEST_MAIN_WAITPID_STATUS=1

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(CFLAGS) $(CFLAGS_$(*))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.txt
