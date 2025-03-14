include ../tlbuild.mk

sub-dir := samples
sub-dir += deprecated

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	@echo USER_FAILED_LOG = ${USER_FAILED_LOG}

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
