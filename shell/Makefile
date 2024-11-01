SHELL = bash

sub-dir := string

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)
	./args.sh
	./array_culling.sh
	./array_elem_replace.sh
	./array_pair.sh
	./array.sh
	./bc.sh
	./call.sh
	./digit.sh
	./dmesg-tail.sh
	./fact.sh
	./ipswap.sh
	./ipv4_check.sh
	./mac.sh
	./nested-func.sh
	./num.sh
	./open-fd.sh
	./parallel.sh
	./pi.sh
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

test:
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

