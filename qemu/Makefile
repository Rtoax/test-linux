include ../tlbuild.mk

sub-dir := tcg/samples/
sub-dir += qcow2

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)

.PHONY: test
test: $(sub-dir-test)
	${Q}$(SHELL) support-cpu.sh
	${Q}$(SHELL) libqemu_examples.sh

.PHONY: clean
clean: $(sub-dir-clean)
	${Q}rm -f *.qcow2 *.raw

include ../template/subdir-footer.mk

