# test-linux make
# By Rong Tao <rongtao@cestc.cn>
#
MAKEFLAGS = --silent --no-print-directory
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))

include make.list
SUB_user_DIR = $(USER_LIST)
SUB_user_DIR_TEST := $(SUB_user_DIR:%=%_test)
SUB_user_DIR_CLEAN := $(SUB_user_DIR:%=%_clean)

SUB_kernel_DIR = $(KERNEL_LIST)
SUB_kernel_DIR_TEST := $(SUB_kernel_DIR:%=%_test)
SUB_kernel_DIR_CLEAN := $(SUB_kernel_DIR:%=%_clean)


all:
	@echo -e "make default: user+kernel"
	@echo -e "make [user|kernel]"
	@echo -e "make [test|testuser|testkernel]"
	@echo -e "make [clean|cleanuser|cleankernel]"

# make_ [U|K] [dir]
define make_
	@echo -e "[$(1)] \033[1;34mMake [$(2)] starting\033[m"
	@cd $(2) ; make ; cd - >/dev/null
	@echo -e "[$(1)] Make [$(2)] done"
endef

# make_test [U|K] [dir]
define make_test
	@echo -e "[$(1)] \033[1;35mTest [$(2)] starting\033[m"
	@cd $(2); make test; cd - >/dev/null
	@echo -e "[$(1)] Test [$(2)] done"
endef

# make_clean [U|K] [dir]
define make_clean
	@echo -e "[$(1)] \033[1;36mClean [$(2)] starting\033[m"
	@cd $(2); make clean; cd - >/dev/null
	@echo -e "[$(1)] Clean [$(2)] done"
endef

default: user kernel
user: $(SUB_user_DIR)
$(SUB_user_DIR):
	$(call make_,U,$@)
kernel: $(SUB_kernel_DIR)
$(SUB_kernel_DIR):
	$(call make_,K,$@)

# Make test
test: testuser testkernel
testuser:$(SUB_user_DIR_TEST)
$(SUB_user_DIR_TEST):
	$(call make_test,U,$(@:%_test=%))
testkernel:$(SUB_kernel_DIR_TEST)
$(SUB_kernel_DIR_TEST):
	$(call make_test,K,$(@:%_test=%))

installdeps:
	sh install-deps.sh

# Make clean
clean:
	@echo "==="
	@echo "=== cleanall"
	@echo "=== cleanuser"
	@echo "=== cleankernel"
	@echo "=== cleangit"
	@echo "==="
cleanall: cleanuser cleankernel cleangit
	echo "=== clean all"
cleanuser: $(SUB_user_DIR_CLEAN)
	echo "=== clean user"
$(SUB_user_DIR_CLEAN):
	$(call make_clean,U,$(@:%_clean=%))
cleankernel: $(SUB_kernel_DIR_CLEAN)
	echo "=== clean kernel"
$(SUB_kernel_DIR_CLEAN):
	$(call make_clean,K,$(@:%_clean=%))
# Clean git repo useless file and directory
cleangit:
	echo "=== clean git repo"
	sh git-clean y

.PHONY: all test clean \
	$(SUB_user_DIR) \
	$(SUB_user_DIR_TEST) \
	$(SUB_user_DIR_CLEAN) \
	$(SUB_kernel_DIR) \
	$(SUB_kernel_DIR_TEST) \
	$(SUB_kernel_DIR_CLEAN)
