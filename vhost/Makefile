include ../tlbuild.mk


sub-dir := vhost-user

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	@echo $(shell ./check.sh)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
