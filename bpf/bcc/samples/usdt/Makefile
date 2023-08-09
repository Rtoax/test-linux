
TARGETS := hello_usdt

# Add more object.o file
hello_usdt: hello_usdt.o

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

test: ${TARGETS}
	./hello_usdt

clean:
	@rm -f ${TARGETS} *.o *.d
