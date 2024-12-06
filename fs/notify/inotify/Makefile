SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS := test

all: ${TARGETS}

test: test.o

clean:
	rm -rf ${TARGETS} *.txt *.o
