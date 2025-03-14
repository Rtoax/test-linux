include ../tlbuild.mk


sub-dir :=
sub-dir += eh_frame
sub-dir += libunwind

$(info INFO: USER_FAILED_LOG = ${USER_FAILED_LOG})

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
