SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS += huiwen
TARGETS += reverse_string_words

all: ${TARGETS}

clean:
	rm -rf ${TARGETS}
