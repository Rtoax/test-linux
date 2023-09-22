
TARGETS += sqrt

ifeq ($(shell uname -m),x86_64)
endif

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
sqrt: sqrt.o

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d *.log
	@rm -rf tmpd-* tmp-*
