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
	bash mkfs.xfs.sh

.PHONY: clean
clean:
	rm -rf tmp-mnt fs.xfs
