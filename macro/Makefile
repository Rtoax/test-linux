
TARGETS :=
TARGETS += align
TARGETS += alias
TARGETS += arch
TARGETS += bit
TARGETS += likely
TARGETS += log
TARGETS += offsetof

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
log: log.o
offsetof: offsetof.o

%.d: %.c
	@echo -e "Generate \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -MM -MF "$@" -MG -MP -MT"$@" -MT"$(<:.c=.o)" $(<)

%.o: %.c %.d
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
