# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
CXX ?= g++
Q ?= @

OS := $(shell grep ^ID= /etc/os-release | sed 's/ID=//g' | sed 's/"//g')
ifeq ($(shell uname -m),x86_64)
else ifeq ($(shell uname -m),aarch64)
endif

sub-dir ?=
kmod-list ?=

CFLAGS += -D_GNU_SOURCE
CFLAGS += -Werror -Wall
# C special, not for C++
CFLAGS += -Wstrict-prototypes

CXXFLAGS += -D_GNU_SOURCE
CXXFLAGS += -Werror -Wall

ifdef DEBUG
  $(info Compile with DEBUG=1)
  CFLAGS += -DDEBUG -O0 -g -ggdb
  CXXFLAGS += -DDEBUG -O0 -g -ggdb
  MAKEFLAGS += DEBUG=1
endif

ifdef ERROR
  $(info Compile with ERROR=1)
  CFLAGS += -DERROR=1
  CXXFLAGS += -DERROR=1
  MAKEFLAGS += ERROR=1
endif

ifdef M32
  $(info Compile 32bit ELF)
  CFLAGS += -m32 -DM32=1
  CXXFLAGS += -m32 -DM32=1
  LDFLAGS += -m32 -DM32=1
  LDXXFLAGS += -m32 -DM32=1
  MAKEFLAGS += M32=1
endif

ifdef FORCE
  CFLAGS += -Wno-error
  CXXFLAGS += -Wno-error
  MAKEFLAGS += FORCE=1
endif

ifdef STATIC
  CFLAGS += -static
  CXXFLAGS += -static
  LDFLAGS += -static
  LDXXFLAGS += -static
  MAKEFLAGS += STATIC=1
endif

ifdef DEBUG
  $(info CFLAGS = ${CFLAGS})
  $(info LDFLAGS = ${LDFLAGS})
  $(info CXXFLAGS = ${CXXFLAGS})
  $(info LDXXFLAGS = ${LDXXFLAGS})
endif

TEMPLATE_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export TEMPLATE_DIR

include ${TEMPLATE_DIR}/../scripts/ansi.mk
include ${TEMPLATE_DIR}/../tlbuild.mk

define git_relative_dir
$(patsubst ${GIT_TOPDIR}/%,%,$(1))
endef

define log_tgt_obj
@printf '  %-8s ${ANSI_BOLD}%s${ANSI_RST} -> ${ANSI_BOLD}%s${ANSI_RST}\n' "${1}" "$(2)" "$(3)"
endef
define log_tgt_exe
@printf '  %-8s ${ANSI_BOLD}%s${ANSI_RST} -> ${ANSI_BOLD}${ANSI_GRE}%s${ANSI_RST}\n' "${1}" "$(2)" "$(3)"
endef
define log_tgt_start
@echo -e "[$(1)] ${ANSI_BOLD}${ANSI_GRE}$(2)${ANSI_RST} start"
endef
define log_tgt_done
@echo -e "[$(1)] ${ANSI_BOLD}${ANSI_YEL}$(2)${ANSI_RST} done"
endef

include ${TEMPLATE_DIR}/../elf/pie.mk
ifneq ($(sub-dir)$(kmod-list),)
  include ${TEMPLATE_DIR}/subdir-header.mk
endif

build-targets := $(TARGETS_PREP)
build-targets += $(OUTPUT)
build-targets += $(TARGETS_LIBA) $(TARGETS_LIBSO)
build-targets += $(TARGETS)
build-targets += $(TARGETS_ASM)
build-targets += $(TARGETS_CPP)
build-targets += $(TARGETS_LLVM_LL)
build-targets += $(TARGETS_BPF)
build-targets += $(TARGETS_RUST)
build-targets += $(TARGETS_CUDA)
build-targets += $(TARGETS_GO)
build-targets += $(TARGETS_JAVA)
TARGETS_SHELL_LOGS := $(patsubst %.sh,%.sh.log,$(TARGETS_SHELL))
build-targets += $(TARGETS_SHELL_LOGS)
TARGETS_PYTHON_LOGS := $(patsubst %.py,%.py.log,$(TARGETS_PYTHON))
build-targets += $(TARGETS_PYTHON_LOGS)
TARGETS_MK_LOGS := $(patsubst %.mk,%.mk.log,$(TARGETS_MK))
build-targets += $(TARGETS_MK_LOGS)
build-targets += $(sub-dir-build) $(kmod-list-build)
build-targets += $(TARGETS_POST)

ifdef DEBUG
  $(info build-targets = ${build-targets})
endif

.PHONY: build
build: $(build-targets)
	$(call log_tgt_done,build,$(call git_relative_dir,$(shell realpath .)))

.PHONY: test
test: $(build-targets) $(sub-dir-test) $(kmod-list-test) $(TARGETS_TEST)
	$(call log_tgt_done,test,$(call git_relative_dir,$(shell realpath .)))

.PHONY: clean
clean: $(sub-dir-clean) $(kmod-list-clean) $(TARGETS_CLEAN)
	$(call log_tgt_start,clean,${build-targets} ${TARGETS_CLEAN})
	${Q}rm -rf ${build-targets} *.o *.d *.log *.out *.class
	${Q}rm -rf *.so *.so.* *.a
	$(call log_tgt_done,clean,$(call git_relative_dir,$(shell realpath .)))

include ${TEMPLATE_DIR}/target-exe.mk
ifneq ($(TARGETS_LIBA),)
  include ${TEMPLATE_DIR}/target-liba.mk
endif
ifneq ($(TARGETS_LIBSO),)
  include ${TEMPLATE_DIR}/target-libso.mk
endif
ifneq ($(HAVE_LLVM)$(TARGETS_LLVM_LL),)
  include ${TEMPLATE_DIR}/target-llvm.mk
endif
ifneq ($(TARGETS_BPF),)
  include ${TEMPLATE_DIR}/target-bpf.mk
endif
ifneq ($(TARGETS_RUST),)
  include ${TEMPLATE_DIR}/target-rust.mk
endif
ifneq ($(TARGETS_CUDA),)
  include ${TEMPLATE_DIR}/target-cuda.mk
endif
ifneq ($(TARGETS_SHELL),)
  include ${TEMPLATE_DIR}/target-shell.mk
endif
ifneq ($(TARGETS_MK_LOGS),)
  include ${TEMPLATE_DIR}/target-make.mk
endif
ifneq ($(TARGETS_PYTHON),)
  include ${TEMPLATE_DIR}/target-python.mk
endif
ifneq ($(TARGETS_GO),)
  include ${TEMPLATE_DIR}/target-golang.mk
endif
ifneq ($(TARGETS_JAVA),)
  include ${TEMPLATE_DIR}/target-java.mk
endif
ifneq (${OUTPUT},)
  include ${TEMPLATE_DIR}/target-output.mk
endif

ifneq ($(sub-dir)$(kmod-list),)
  include ${TEMPLATE_DIR}/subdir-footer.mk
endif
