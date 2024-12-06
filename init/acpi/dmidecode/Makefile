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
	./memory.sh
	./oem.sh
	./product.sh
	./serial-number.sh
	./string.sh
	./type.sh

.PHONY: clean
clean:
