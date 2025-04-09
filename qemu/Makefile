include ../tlbuild.mk

sub-dir := tcg/samples/

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: test
test: $(sub-dir-test)
	@$(SHELL) support-cpu.sh

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -f *.qcow2 *.raw

include ../template/subdir-footer.mk

