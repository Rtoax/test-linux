SHELL = bash
include ../tlbuild.mk


sub-dir := posix

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	${Q}make -C $(@:.clean=) clean
