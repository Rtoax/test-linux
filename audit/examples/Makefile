SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


.PHONY: all
all:

.PHONY: test
test:
	@$(SHELL) file.sh

.PHONY: clean
clean:
	${Q}rm -f tmpfile-*.out
