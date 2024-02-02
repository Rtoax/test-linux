
TARGETS += poison
TARGETS += GCC_diagnostic
TARGETS += GCC_target
TARGETS += pragma-message
TARGETS += call-func
TARGETS += push_macro

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -I../../
CFLAGS += -pthread

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

poison: poison.o
GCC_diagnostic: GCC_diagnostic.o
GCC_target: GCC_target.o
pragma-message: pragma-message.o
call-func: call-func.o
push_macro: push_macro.o

# TODO
CFLAGS_call-func := -Wno-unknown-pragmas

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	$(call print_elf,$(@))

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS)
	$(call print_elf,$(@))

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} \
		*.o *.d *.out

