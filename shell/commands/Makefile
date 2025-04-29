# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk

sub-dir :=
sub-dir += awk
sub-dir += dmesg
sub-dir += grep
sub-dir += sed

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) test
	@echo -e "  \033[1;33mDone\033[m"

.PHONY: test
test: $(sub-dir-test)
	@echo -e "  \033[1;33mTEST\033[m"
	@./bc.sh
	@./tr.sh

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	${Q}rm -f *.log

include ../../template/subdir-footer.mk

