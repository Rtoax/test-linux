
TARGETS :=
TARGETS += offsetof
TARGETS += likely

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

offsetof: offsetof.o
likely: likely.o

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
