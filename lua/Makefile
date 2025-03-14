include ../tlbuild.mk


sub-dir :=

LUA = $(shell which lua 2>/dev/null)

TARGETS :=

ifeq ($(wildcard $(LUA)),)
  TARGETS :=
  $(warning Please install lua)
endif

include ../template/subdir-header.mk


.PHONY: build
build: test

.PHONY: test
test: $(sub-dir-test)
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@./cmd

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.so*

include ../template/subdir-footer.mk
