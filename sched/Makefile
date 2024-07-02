
TARGETS += current
TARGETS += uninterruptible
TARGETS += hung
TARGETS += zombie
TARGETS += stopped

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
current: current.o
uninterruptible: uninterruptible.o
hung: hung.o
zombie: zombie.o
stopped: stopped.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

kill-uninterruptible:
	kill $(shell pgrep uninterruptible)

kill-zombie:
	kill $(shell pgrep zombie)

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d
