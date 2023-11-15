
TARGETS := clock_getres
TARGETS += clock_gettime clock_gettime-CLOCK_BOOTTIME
TARGETS += clock_nanosleep

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS += -pthread
CFLAGS += -I../../../
CFLAGS += -I../

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
clock_getres: clock_getres.o helpers.o
clock_gettime: clock_gettime.o helpers.o
clock_gettime-CLOCK_BOOTTIME: clock_gettime-CLOCK_BOOTTIME.o helpers.o
clock_nanosleep: clock_nanosleep.o helpers.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.txt
