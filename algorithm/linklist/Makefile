SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS += reverse_list
TARGETS += list_del

all: ${TARGETS}

clean:
	rm -rf ${TARGETS}
