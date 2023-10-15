
TARGETS += array
TARGETS += compat
TARGETS += ptr-dim
TARGETS += xor
TARGETS += __label__
TARGETS += __typeof__

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../macro/

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g -ggdb
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
array: array.o
compat: compat.o
ptr-dim: ptr-dim.o helpers.o
xor: xor.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
