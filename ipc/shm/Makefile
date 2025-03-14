include ../../tlbuild.mk


sub-dir := linklist
sub-dir += sysv
sub-dir += mmap

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
