include ../../tlbuild.mk


sub-dir :=

include ../../template/subdir-header.mk

.PHONY: build
build: $(sub-dir-build) test
	@echo -e "  \033[1;33mDone\033[m"

.PHONY: test
test: $(sub-dir-test)
	@echo -e "  \033[1;33mTEST\033[m"
	./ipswap.sh
	./ipv4_check.sh
	./mac.sh

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"

include ../../template/subdir-footer.mk

