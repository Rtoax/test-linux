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
	$(Q)bash mkfs.xfs.sh

.PHONY: clean
clean:
	$(Q)sudo umount tmp-mnt || true
	$(Q)sudo rm -rf tmp-mnt fs.xfs
