include ../tlbuild.mk


sub-dir := tcg/samples/

$(info INFO: USER_FAILED_LOG = ${USER_FAILED_LOG})

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: $(sub-dir-build)

.PHONY: test
test:
	@$(SHELL) support-cpu.sh

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -f *.qcow2 *.raw

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean

