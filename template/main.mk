# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
ifndef _MAIN_MK
_MAIN_MK = 1

CC ?= gcc
CXX ?= g++
AS ?= as
NASM ?= nasm
OBJCOPY ?= objcopy
subdir-y ?=

include cflags.mk
include mkflags.mk
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
build-targets += $(target-as-y)
build-targets += $(target-asm-y) $(target-asm-std-y)
build-targets += $(target-cpp-y)
build-targets += $(target-llvm-ll-y)
build-targets += $(call append_output_prefix,${target-bpf-y}) # ${OUTPUT}/.bpf.o
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

SRC_SFX_LIST := $(shell seq 1 1 10)
# %.1 %.2 ...
MK_TGT_SFX_LIST := $(patsubst %,\%.%,${SRC_SFX_LIST})

# $1: target name, like shell in target-shell-y
# $2: target extension, like .sh for shell, could be a list
# $3: log extension, like .log, .prog.log
define add_target_program
# without .N suffix
target-${1}-y-orig := $$(filter-out $${MK_TGT_SFX_LIST},$$(target-${1}-y))
# log with .N suffix
$$(if ${ext}, \
  $$(foreach ext, ${2}, \
    $$(eval target-${1}-y-sfx := $$(filter-out $${target-${1}-y-orig},$$(target-${1}-y))) \
    $$(foreach sfx, $${SRC_SFX_LIST}, \
      $$(eval target-${1}-y-sfx := $$(patsubst %${ext}.$${sfx},$${OUTPUT}%${ext}${3}.$${sfx},$$(target-${1}-y-sfx))) \
    ) \
  ), \
  $$(eval target-${1}-y-sfx := $$(filter-out $${target-${1}-y-orig},$$(target-${1}-y))) \
  $$(foreach sfx, $${SRC_SFX_LIST}, \
    $$(eval target-${1}-y-sfx := $$(patsubst %.$${sfx},$${OUTPUT}%${3}.$${sfx},$$(target-${1}-y-sfx))) \
  ) \
)
# all logs
build-targets += $$(patsubst %,$${OUTPUT}%${3},$$(target-${1}-y-orig)) $${target-${1}-y-sfx}
endef

$(eval $(call add_target_program,prog,,.prog.log))
$(eval $(call add_target_program,shell,.sh,.log))
$(eval $(call add_target_program,mk,.mk .mak,.log))
$(eval $(call add_target_program,python,.py,.log))
$(eval $(call add_target_program,bt,.bt,.log))

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
	$(call log_warn,Build)
	$(call log_obj,BUILD DONE,$(call strip_topdir_prefix,$(shell realpath .)))

.PHONY: test
test: $(build-targets) $(subdir-y-test) $(target-test-y)
	$(call log_warn,Test)
	$(call log_obj,TEST DONE,$(call strip_topdir_prefix,$(shell realpath .)))

.PHONY: clean
clean: $(subdir-y-clean) $(target-clean-y)
	$(call log_warn,Clean)
	$(call log_tgt,CLEAN,${build-targets} ${target-clean-y})
	${Q}rm -rf ${build-targets}
	${Q}rm -f *.o *.o.d
	${Q}rm -f *.log *.out *.class
	${Q}rm -f *.so *.so.* *.a
	${Q}rm -f *.dat *.bin
	$(call log_obj,CLEAN DONE,$(call strip_topdir_prefix,$(shell realpath .)))

.PHONY: reset
reset:
	$(call log_warn,Reset)
	$(call log_reset_files)

.PHONY: done
done:
	$(call log_warn,Done)
	$(call log_display_failed)

# All helpers, only include targets/helpers.mk if helpers.mk was included.
ifdef _HELPERS_MK
  include targets/helpers.mk
endif

ifneq (${OUTPUT},)
  include targets/output.mk
endif
include targets/asm.mk
include targets/c.mk
include targets/cpp.mk
ifneq ($(target-liba-y),)
  include targets/liba.mk
endif
ifneq ($(target-libso-y)$(target-libso-cpp-y),)
  include targets/libso.mk
endif
ifneq ($(target-llvm-ll-y),)
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

include targets/vdso.mk
include targets/compiler.mk

endif
