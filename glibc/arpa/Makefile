SHELL = bash

MAKE_SUB_ARGS :=

sub-dir := inet

sub-dir-build := $(sub-dir:=.build)
sub-dir-clean := $(sub-dir:=.clean)

ifdef M32
  MAKE_SUB_ARGS += M32=1
endif

.PHONY: build
build: $(sub-dir-build)

.PHONY: clean
clean: $(sub-dir-clean)

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	@make -C $(@:.build=) ${MAKE_SUB_ARGS}
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	@make -C $(@:.clean=) clean
