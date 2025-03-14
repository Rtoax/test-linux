include ../tlbuild.mk

sub-dir := demos

include ../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	${Q}$(SHELL) ./README.sh

.PHONY: clean
clean: $(sub-dir-clean)

include ../template/subdir-footer.mk
