SHELL = bash

sub-dir :=
sub-dir += alias
sub-dir += commands
sub-dir += math
sub-dir += network
sub-dir += string

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build) test
	@echo -e "  \033[1;33mDone\033[m"

.PHONY: test
test:
	@echo -e "  \033[1;33mTEST\033[m"
	./args.sh
	./array_culling.sh
	./array_elem_replace.sh
	./array_pair.sh
	./array.sh
	./call.sh
	./digit.sh
	./dmesg-tail.sh
	./nested-func.sh
	./num.sh
	./open-fd.sh
	./parallel.sh
	./replace.sh
	./ret.sh
	sudo ./root-chk.sh
	echo 3 | ./select.sh
	./stat.sh /etc/os-release /etc/fstab /etc/hosts
	./tracing.sh
	./trap.sh
	./while.sh
	./cmdline.sh ignition.firstboot=1
	./cmdline.sh ignition.firstboot=0
	./cmdline.sh ignition.firstboot=on
	./cmdline.sh ignition.firstboot=off
	./cmdline.sh ignition.firstboot

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"
	@rm -f a.txt *.log tmp.sh

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean

