SHELL = bash
include ../../tlbuild.mk

.PHONY: build
build:
	$(Q)bash mkfs.xfs.sh

.PHONY: clean
clean:
	$(Q)sudo umount tmp-mnt || true
	$(Q)sudo rm -rf tmp-mnt fs.xfs
