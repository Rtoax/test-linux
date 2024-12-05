SHELL = bash

sub-dir := samples

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@make -C $(@:.build=)
$(sub-dir-clean):
	@make -C $(@:.clean=) clean
