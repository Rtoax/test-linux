include ../../tlbuild.mk


sub-dir := samples

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build)
	${Q}./check.sh
	@echo -e " \033[1;33m Done \033[m"

.PHONY: clean
clean: $(sub-dir-clean)

include ../../template/subdir-footer.mk
