include ../tlbuild.mk

sub-dir :=
sub-dir += eh_frame
sub-dir += libunwind

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
