
TARGETS += asctime asctime_r
TARGETS += localtime localtime_r
TARGETS += clock
TARGETS += clock_getcpuclockid

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
asctime: asctime.o
asctime_r: asctime_r.o
localtime: localtime.o
localtime_r: localtime_r.o
clock: clock.o
clock_getcpuclockid: clock_getcpuclockid.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
