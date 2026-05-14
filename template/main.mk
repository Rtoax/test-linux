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

$(if $(subdir-y), $(eval include targets/subdir-header.mk))

build-targets += $(target-prep-y)
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

# 1 2 3 ...
SRC_SFX_LIST ?= $(shell seq 1 1 10)
# %.1 %.2 %.3 ...
MK_TGT_SFX_LIST := $(patsubst %,\%.%,${SRC_SFX_LIST})

# append_program_target() - add program to build-targets
#
# If you want to test a program twice, add a .N suffix to the program, for
# example: target-prog-y := a.sh a.sh.1
#
# Arguments:
# $1: target name, like shell in target-shell-y
# $2: target extension, like .sh for shell, could be a list
# $3: log extension, like .log, .prog.log
define append_program_target
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

# see targets/{prog,shell,make,python,bpftrace}.mk
$(if ${target-prog-y}, $(eval $(call append_program_target,prog,,.prog.log)))
$(if ${target-shell-y}, $(eval $(call append_program_target,shell,.sh,.log)))
$(if ${target-mk-y}, $(eval $(call append_program_target,mk,.mk .mak,.log)))
$(if ${target-python-y}, $(eval $(call append_program_target,python,.py,.log)))
$(if ${target-bt-y}, $(eval $(call append_program_target,bt,.bt,.log)))

ifeq (${KMOD}, y)
  $(if ${__KMOD__}, $(eval build-targets += kmods-build))
  $(if ${__KMOD__}, $(eval target-clean-y += kmods-clean))
endif
build-targets += $(subdir-y-build)
build-targets += $(target-post-y)

ifneq (${DRY_RUN},)
  build-targets := $(subdir-y-build)
endif

ifdef DEBUG
  $(info build-targets = ${build-targets})
  $(info SRC_SFX_LIST = ${SRC_SFX_LIST})
endif

.PHONY: build
build: $(build-targets)
	$(call log_warn,Build)
	$(call log_obj,BUILD DONE,$(call strip_topdir_prefix,$(shell realpath .)))

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
	$(call log_reset)

.PHONY: done
done:
	$(call log_warn,Done)
	$(call log_display_failed)

# All helpers, only include targets/helpers.mk if helpers.mk was included.
$(if ${_HELPERS_MK}, $(eval include targets/helpers.mk))
$(if ${OUTPUT}, $(eval include targets/output.mk))
include targets/asm.mk
include targets/c.mk
include targets/cpp.mk
$(if $(target-liba-y), $(eval include targets/liba.mk))
$(if $(target-libso-y)$(target-libso-cpp-y), $(eval include targets/libso.mk))
$(if $(target-llvm-ll-y), $(eval include targets/llvm.mk))
$(if $(target-bpf-y)$(target-btf-y), $(eval include targets/bpf.mk))
$(if $(target-rust-y), $(eval include targets/rust.mk))
$(if $(target-nvcc-y)$(target-nvcc-libso-y)$(target-nvcc-liba-y), $(eval include targets/cuda.mk))
$(if $(target-hipcc-y)$(target-hipcc-libso-y)$(target-hipcc-liba-y), $(eval include targets/hip.mk))
$(if $(target-htcc-y)$(target-htcc-libso-y)$(target-htcc-liba-y), $(eval include targets/hpcc.mk))
$(if $(target-lscc-y)$(target-lscc-libso-y)$(target-lscc-liba-y), $(eval include targets/luca.mk))
$(if $(target-shell-y), $(eval include targets/shell.mk))
$(if $(target-prog-y), $(eval include targets/prog.mk))
$(if $(target-mk-y), $(eval include targets/make.mk))
$(if $(target-bt-y), $(eval include targets/bpftrace.mk))
$(if $(target-python-y), $(eval include targets/python.mk))
$(if $(target-go-y), $(eval include targets/golang.mk))
$(if $(target-java-y), $(eval include targets/java.mk))
ifeq (${KMOD}, y)
  # __KMOD__ defined in scripts/make_tl.sh
  $(if ${__KMOD__}, $(eval include targets/kmod.mk))
endif
$(if $(subdir-y), $(eval include targets/subdir-footer.mk))
include targets/vdso.mk
include targets/compiler.mk

endif
