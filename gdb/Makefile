
TARGETS := set-value
TARGETS += set-value-func
TARGETS += set-value-volatile
TARGETS += global-var

CC = gcc
CFLAGS := -Werror -Wall
CFLAGS += -O3 -ggdb
CXXFLAGS :=
CXXFLAGS += -O0 -ggdb

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
set-value: set-value.o
set-value-func: set-value-func.o
set-value-volatile: set-value-volatile.o

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
