# SPDX-License-Identifier: GPL-3.0
include ../tlbuild.mk

sub-dir :=
sub-dir += alias
sub-dir += array
sub-dir += commands
sub-dir += math
sub-dir += network
sub-dir += string

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) test
	@echo -e "  \033[1;33mDone\033[m"

.PHONY: test
test: $(sub-dir-test)
	@echo -e "  \033[1;33mTEST\033[m"
	./args.sh
	./call.sh
	./digit.sh
	./nested-func.sh
	./num.sh
	./open-fd.sh
	./parallel.sh
	./replace.sh
	./ret.sh
	./root-chk.sh
	./select.sh
	./stat.sh /etc/os-release /etc/hosts
	./tracing.sh
	./trap.sh
	./while.sh
	./cmdline.sh
	./sudo.sh
	./c_code.sh

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	${Q}rm -f a.txt *.log tmp.sh *.out

include ../template/subdir-footer.mk

