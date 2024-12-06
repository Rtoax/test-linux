SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += bsearch

CC = gcc

all: ${TARGETS}

clean:
	rm -rf ${TARGETS}
