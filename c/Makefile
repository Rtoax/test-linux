
TARGETS += auto
TARGETS += array
TARGETS += ascii
TARGETS += param-pass
TARGETS += compat
TARGETS += _Generic
TARGETS += ptr-dim
TARGETS += xor
TARGETS += __alignof__
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

CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
auto: auto.o
ascii: ascii.o
param-pass: param-pass.o
array: array.o
compat: compat.o
_Generic: _Generic.o
ptr-dim: ptr-dim.o helpers.o
xor: xor.o
__alignof__: __alignof__.o

CFLAGS__Generic := -Wno-all

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s
