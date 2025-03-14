include ../tlbuild.mk


sub-dir := atomic
sub-dir += semaphore
sub-dir += mcs_spinlock/dpdk

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
