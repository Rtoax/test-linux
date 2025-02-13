SHELL = bash
include ../../tlbuild.mk



TARGETS := watchdog-simple

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

CFLAGS :=

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

clean:
	rm -f ${TARGETS} *.o *.d
