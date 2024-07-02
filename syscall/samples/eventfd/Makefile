
TARGETS := epoll
TARGETS += eventfd_read
TARGETS += eventfd-irq
TARGETS += eventfd-latency

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
epoll: epoll.o
eventfd_read: eventfd_read.o utils.o
eventfd-irq: eventfd-irq.o utils.o
eventfd-latency: eventfd-latency.o utils.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
