
TARGETS := set-value
TARGETS += set-value-ok

CC = gcc
CFLAGS := -Werror -Wall
CFLAGS += -O3 -ggdb

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
set-value: set-value.o
set-value-ok: set-value-ok.o

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
