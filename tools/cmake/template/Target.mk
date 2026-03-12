.PHONY: build0
build0:
	@echo -e " \033[1;33m Building User \033[m"
	${Q}make -f Makefile.user
	${Q}mkdir -p build && pushd build && cmake .. && make && popd
	@echo -e " \033[1;33m Building Kernel \033[m"
	${Q}make -f Makefile.kernel

.PHONY: clean0
clean0:
	${Q}make clean -f Makefile.user
	${Q}make clean -f Makefile.kernel
	${Q}rm -rf build
