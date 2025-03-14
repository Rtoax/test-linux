include ../../tlbuild.mk


sub-dir :=

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) test
	@echo -e "  \033[1;33mDone\033[m"

.PHONY: test
test: $(sub-dir-test)
	@echo -e "  \033[1;33mTEST\033[m"
	./array_culling.sh
	./array_elem_replace.sh
	./array_pair.sh
	./array.sh

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"

include ../../template/subdir-footer.mk

