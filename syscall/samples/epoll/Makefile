TARGETS := eventfd
TARGETS += level-triggered edge-triggered
TARGETS += tcp-echo

CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -DDEBUG -O0 -g
# CFLAGS += -DUSE_ONESHOT=1

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
eventfd: eventfd.o
level-triggered: level-triggered.o
edge-triggered: edge-triggered.o
tcp-echo: tcp-echo.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(@)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
