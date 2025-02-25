include ../../tlbuild.mk

.PHONY: all
all:
	${Q}./ldd.sh
	${Q}ld.so --list-tunables | grep rtld
	@echo -e " \033[1;33m DONE \033[m"

.PHONY: clean
clean:
	@echo -e " \033[1;33m clean \033[m"
