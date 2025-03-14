# SPDX-License-Identifier: GPL-3.0
include ../../../tlbuild.mk


sub-dir := basic
sub-dir += icmp
sub-dir += iproute2
sub-dir += prog-test-run
#sub-dir += xdp_count

include ../../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../../../template/subdir-footer.mk
