SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS := select
TARGETS += heap-1 heap-2
TARGETS += insert
TARGETS += merge
TARGETS += quick-1 quick-2

CC = gcc

all: ${TARGETS}

clean:
	rm -rf ${TARGETS}
