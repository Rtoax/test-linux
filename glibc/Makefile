
TARGETS := nr_errno
TARGETS += gnu_get_libc_version

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
	$(shell sh errno.sh)

nr_errno: nr_errno.o
gnu_get_libc_version: gnu_get_libc_version.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d *.out \
		nr_errno.h

