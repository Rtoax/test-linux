include ../../tlbuild.mk


sub-dir :=

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))

.PHONY: build
build: $(sub-dir-build) test
	@echo -e "  \033[1;33mDone\033[m"

.PHONY: test
test:
	@echo -e "  \033[1;33mTEST\033[m"
	./array_culling.sh
	./array_elem_replace.sh
	./array_pair.sh
	./array.sh

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(@)\033[m"

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean

