
TARGETS :=
TARGETS += align
TARGETS += alias
TARGETS += arch
TARGETS += bit
TARGETS += likely
TARGETS += offsetof
TARGETS += __clang__
TARGETS += __i386__
TARGETS += __x86_64__

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -O0

ifdef DEBUG
CFLAGS += -DDEBUG -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

arch: arch.o
align: align.o
alias: alias.o
bit: bit.o
likely: likely.o
offsetof: offsetof.o
__clang__: __clang__.o
__i386__: __i386__.o
__x86_64__: __x86_64__.o

CFLAGS___i386__ := -m32
CFLAGS___x86_64__ := -m64

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^)

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
