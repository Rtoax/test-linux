
TARGETS := nr_errno
TARGETS += EDOM

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: nr_errno.h ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

nr_errno.h:
	$(shell bash errno.sh)

nr_errno: nr_errno.o

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d *.out \
		nr_errno.h

