# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
ifndef _MAIN_MK
_MAIN_MK = 1

CC ?= gcc
CXX ?= g++
OBJCOPY ?= objcopy
Q ?= @

ifeq ($(shell uname -m),x86_64)
else ifeq ($(shell uname -m),aarch64)
endif

subdir-y ?=

CFLAGS += -D_GNU_SOURCE
CFLAGS += -Werror -Wall
# C special, not for C++
CFLAGS += -Wstrict-prototypes

CXXFLAGS += -D_GNU_SOURCE
CXXFLAGS += -Werror -Wall

ifdef DEBUG
  $(info Compile with DEBUG=1)
  CFLAGS += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS_A += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS_SO += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CFLAGS_BPF += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS_A += -DDEBUG=${DEBUG} -O0 -g -ggdb
  CXXFLAGS_SO += -DDEBUG=${DEBUG} -O0 -g -ggdb
  MAKEFLAGS += DEBUG=${DEBUG}
endif

ifdef ERROR
  $(info Compile with ERROR=${ERROR})
  CFLAGS += -DERROR=${ERROR}
  CFLAGS_A += -DERROR=${ERROR}
  CFLAGS_SO += -DERROR=${ERROR}
  CFLAGS_BPF += -DERROR=${ERROR}
  CXXFLAGS += -DERROR=${ERROR}
  MAKEFLAGS += ERROR=${ERROR}
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

include pie.mk
CFLAGS += ${CFLAGS_PIE}
LDFLAGS += ${LDFLAGS_PIE}

include shell.mk
include ansi.mk
include user.mk
include verbose.mk
include arch.mk
include dir.mk
include log.mk

ifneq ($(subdir-y),)
  include targets/subdir-header.mk
endif

build-targets := $(target-prep-y)
build-targets += $(OUTPUT)
build-targets += $(target-liba-y) $(target-libso-y) $(target-libso-cpp-y)
build-targets += $(target-y)
build-targets += $(target-asm-y)
build-targets += $(target-cpp-y)
build-targets += $(target-llvm-ll-y)
build-targets += $(target-bpf-y)
build-targets += $(target-btf-y)
build-targets += $(target-rust-y)
build-targets += $(target-nvcc-y)
build-targets += $(target-nvcc-libso-y)
build-targets += $(target-nvcc-liba-y)
build-targets += $(target-hipcc-y)
build-targets += $(target-hipcc-libso-y)
build-targets += $(target-hipcc-liba-y)
build-targets += $(target-htcc-y)
build-targets += $(target-htcc-libso-y)
build-targets += $(target-htcc-liba-y)
build-targets += $(target-lscc-y)
build-targets += $(target-lscc-libso-y)
build-targets += $(target-lscc-liba-y)
build-targets += $(target-go-y)
build-targets += $(target-java-y)

src-sfx-list := 1 2 3 4 5 6 7 8 9 10
# %.1 %.2 ...
tgt-sfx-list :=
$(foreach sfx, ${src-sfx-list}, $(eval tgt-sfx-list += %.${sfx}))

# prog without .N suffix
target-prog-y-orig := $(filter-out ${tgt-sfx-list},$(target-prog-y))
# prog with .N suffix
target-prog-y-sfx := $(filter-out ${target-prog-y-orig},$(target-prog-y))
# prog log with .N suffix
$(foreach sfx, ${src-sfx-list}, \
  $(eval target-prog-y-sfx := $(patsubst %.${sfx},${OUTPUT}%.prog.log.${sfx},$(target-prog-y-sfx))) \
)
# all prog logs
build-targets += $(patsubst %,${OUTPUT}%.prog.log,$(target-prog-y-orig)) ${target-prog-y-sfx}

# $1: target name, like shell in target-shell-y
# $2: target short name, like sh for shell
define add_target_program
# without .N suffix
target-${1}-y-orig := $$(filter-out $${tgt-sfx-list},$$(target-${1}-y))
# with .N suffix
target-${1}-y-sfx := $$(filter-out $${target-${1}-y-orig},$$(target-${1}-y))
# log with .N suffix
$$(foreach sfx, $${src-sfx-list}, \
  $$(eval target-${1}-y-sfx := $$(patsubst %.${2}.$${sfx},$${OUTPUT}%.${2}.log.$${sfx},$$(target-${1}-y-sfx))) \
)
# all logs
build-targets += $$(patsubst %,$${OUTPUT}%.log,$$(target-${1}-y-orig)) $${target-${1}-y-sfx}
endef

$(eval $(call add_target_program,shell,sh))
$(eval $(call add_target_program,mk,mk))
$(eval $(call add_target_program,mk,mak))
$(eval $(call add_target_program,python,py))
$(eval $(call add_target_program,bt,bt))

build-targets += $(subdir-y-build)
build-targets += $(target-post-y)


ifdef DEBUG
  $(info CFLAGS = ${CFLAGS})
  $(info LDFLAGS = ${LDFLAGS})
  $(info CXXFLAGS = ${CXXFLAGS})
  $(info LDXXFLAGS = ${LDXXFLAGS})
  $(info build-targets = ${build-targets})
endif

export CFLAGS LDFLAGS CXXFLAGS LDXXFLAGS MAKEFLAGS

.PHONY: build
build: $(build-targets)
	$(call log_obj,BUILD DONE,$(call strip_topdir_prefix,$(shell realpath .)))

.PHONY: test
test: $(build-targets) $(subdir-y-test) $(target-test-y)
	$(call log_obj,TEST DONE,$(call strip_topdir_prefix,$(shell realpath .)))

.PHONY: clean
clean: $(subdir-y-clean) $(target-clean-y)
	$(call log_tgt,CLEAN,${build-targets} ${target-clean-y})
	${Q}rm -rf ${build-targets}
	${Q}rm -f *.o *.log *.out *.class
	${Q}rm -f *.so *.so.* *.a
	${Q}rm -f *.dat *.bin
	$(call log_obj,CLEAN DONE,$(call strip_topdir_prefix,$(shell realpath .)))

.PHONY: reset
reset:
	@echo "Reset"
	$(call log_reset_files)

.PHONY: done
done:
	@echo "Done"
	$(call log_display_failed)

# Helpers
include targets/helpers.mk

ifneq (${OUTPUT},)
  include targets/output.mk
endif
include targets/exe.mk
ifneq ($(target-liba-y),)
  include targets/liba.mk
endif
ifneq ($(target-libso-y)$(target-libso-cpp-y),)
  include targets/libso.mk
endif
ifneq ($(USE_LLVM)$(target-llvm-ll-y),)
  include targets/llvm.mk
endif
ifneq ($(target-bpf-y)$(target-btf-y),)
  include targets/bpf.mk
endif
ifneq ($(target-rust-y),)
  include targets/rust.mk
endif
ifneq ($(target-nvcc-y)$(target-nvcc-libso-y)$(target-nvcc-liba-y),)
  include targets/cuda.mk
endif
ifneq ($(target-hipcc-y)$(target-hipcc-libso-y)$(target-hipcc-liba-y),)
  include targets/hip.mk
endif
ifneq ($(target-htcc-y)$(target-htcc-libso-y)$(target-htcc-liba-y),)
  include targets/hpcc.mk
endif
ifneq ($(target-lscc-y)$(target-lscc-libso-y)$(target-lscc-liba-y),)
  include targets/luca.mk
endif
ifneq ($(target-shell-y),)
  include targets/shell.mk
endif
ifneq ($(target-prog-y),)
  include targets/prog.mk
endif
ifneq ($(target-mk-y),)
  include targets/make.mk
endif
ifneq ($(target-bt-y),)
  include targets/bpftrace.mk
endif
ifneq ($(target-python-y),)
  include targets/python.mk
endif
ifneq ($(target-go-y),)
  include targets/golang.mk
endif
ifneq ($(target-java-y),)
  include targets/java.mk
endif

ifneq ($(subdir-y),)
  include targets/subdir-footer.mk
endif

endif
