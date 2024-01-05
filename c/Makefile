
TARGETS += auto
TARGETS += array
TARGETS += ascii
TARGETS += alignas
TARGETS += case
TARGETS += const
TARGETS += param-pass
TARGETS += compat
TARGETS += compare
TARGETS += _Generic
TARGETS += ptr-dim
TARGETS += struct
TARGETS += xor
TARGETS += __alignof__
TARGETS += __label__
TARGETS += __typeof__
TARGETS += NULL
TARGETS += _Nullable
TARGETS += _Nonnull
TARGETS += BUILD_BUG_ON_ZERO
TARGETS += macro

ifeq ($(shell uname -m),x86_64)
endif
ifeq ($(shell uname -m),aarch64)
endif

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

LDFLAGS :=
LDLIBS :=

CFLAGS := -Werror -Wall
CFLAGS += -I../macro/
ifdef STATIC
CFLAGS += -static
$(info Defined STATIC)
endif

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g -ggdb
endif

CFLAGS_auto := -Wno-error=implicit-int
CFLAGS_param-pass := -O0 -I../macro/
CFLAGS_alignas := -std=gnu17

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
auto: auto.o
ascii: ascii.o
alignas: alignas.o
case: case.o
const: const.o
param-pass: param-pass.o
array: array.o
compat: compat.o
compare: compare.o
_Generic: _Generic.o
ptr-dim: ptr-dim.o helpers.o
struct: struct.o
xor: xor.o
__alignof__: __alignof__.o
__label__: __label__.o
__typeof__: __typeof__.o
NULL: NULL.o
_Nullable: _Nullable.o
_Nonnull: _Nonnull.o
BUILD_BUG_ON_ZERO: BUILD_BUG_ON_ZERO.o
macro: macro.o

CFLAGS__Generic := -Wno-all

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -E $(<) -o $(<:.c=.E.c)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.s *.E.c
