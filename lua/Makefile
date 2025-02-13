include ../tlbuild.mk


sub-dir :=

LUA = $(shell which lua 2>/dev/null)

TARGETS :=

ifeq ($(wildcard $(LUA)),)
  TARGETS :=
  $(warning Please install lua)
endif

sub-dir-build := $(addprefix $(shell pwd)/,$(sub-dir:=.build))
sub-dir-clean := $(addprefix $(shell pwd)/,$(sub-dir:=.clean))


.PHONY: build
build: test

.PHONY: test
test:
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	@./cmd

.PHONY: clean
clean: $(sub-dir-clean)
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.so*

$(sub-dir-build):
	@echo -e "\033[1;32m [sub-dir] build $(@)\033[m"
	${Q}make -C $(@:.build=)
$(sub-dir-clean):
	@echo -e "\033[1;32m [sub-dir] clean $(@)\033[m"
	${Q}make -C $(@:.clean=) clean
