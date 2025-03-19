include ../../tlbuild.mk

.PHONY: build
build:
	$(Q)bash mkfs.fat.sh

.PHONY: clean
clean:
	$(Q)sudo umount tmp-mnt || true
	$(Q)sudo rm -rf tmp-mnt fat.fs
