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
	$(Q)bash mkfs.ext4.sh

.PHONY: clean
clean:
	$(Q)rm -rf tmp-mnt fs.ext4
