$(info INFO: This is info)
$(warning WARNING: This is warning)
#$(error ERROR: This error)

.PHONY: all
all:
	@echo -e " \033[1;33m Building User \033[m"
	make -f Makefile.user
	mkdir -p build && pushd build && cmake .. && make && popd
	@echo -e " \033[1;33m Building Kernel \033[m"
	make -f Makefile.kernel

.PHONY: clean
clean:
	make clean -f Makefile.user
	make clean -f Makefile.kernel
	rm -rf build
