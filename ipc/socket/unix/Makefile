SHELL = bash

sub-dir := rate
sub-dir += simple
sub-dir += select

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
all: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
