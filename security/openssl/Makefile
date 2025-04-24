# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include openssl.mk

sub-dir := asn.1
sub-dir += commands
sub-dir += hello
sub-dir += samples

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
