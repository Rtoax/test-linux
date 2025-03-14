include ../../tlbuild.mk

sub-dir := dmidecode

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	./support.sh

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
