# test-linux make
# By Rong Tao <rongtao@cestc.cn>
#
MAKEFLAGS = --silent --no-print-directory
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

SUB_DIR = $(shell cat make.list)
SUB_DIR_TEST := $(SUB_DIR:%=%_test)
SUB_DIR_CLEAN := $(SUB_DIR:%=%_clean)

all: $(SUB_DIR)

$(SUB_DIR):
	@echo -e "\033[1;34mMake [$@] starting\033[m"
	@cd $@ ; make ; cd -
	@echo -e "Make [$@] done"

# Make test
test:$(SUB_DIR_TEST)

$(SUB_DIR_TEST):
	@echo -e "\033[1;35mTest [$(@:%_test=%)] starting\033[m"
	@cd $(@:%_test=%); make test; cd -
	@echo -e "Test [$(@:%_test=%)] done"

# Make clean
clean:$(SUB_DIR_CLEAN)

$(SUB_DIR_CLEAN):
	@echo -e "\033[1;36mClean [$(@:%_clean=%)] starting\033[m"
	@cd $(@:%_clean=%); make clean; cd -
	@echo -e "Clean [$(@:%_clean=%)] done"

.PHONY: all test clean $(SUB_DIR) $(SUB_DIR_TEST) $(SUB_DIR_CLEAN)
