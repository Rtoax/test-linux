SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q

.PHONY: build
build:
	$(Q)bash info.sh

.PHONY: clean
clean:
