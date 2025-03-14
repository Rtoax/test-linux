include ../../tlbuild.mk

sub-dir := cache-misses
sub-dir += out-of-order
sub-dir += samples
sub-dir += scripts
ifeq ($(shell uname -m),x86_64)
  sub-dir += pthread_self
endif

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
