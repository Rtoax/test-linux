SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


all:
	sh list_usdt.sh
	sh list_uprobe.sh

test:
clean:
