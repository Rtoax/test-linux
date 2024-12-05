SHELL = bash

sub-dir := breakfast

TARGETS :=
ifeq ($(shell uname -m),x86_64)
TARGETS += int3
endif
ifeq ($(shell uname -m),aarch64)
TARGETS += brk
endif

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build) $(TARGETS)

int3: int3.o
brk: brk.o

.PHONY: clean
clean: $(sub-dir-clean)
	rm -f $(TARGETS) *.o

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
