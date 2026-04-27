# SPDX-License-Identifier: GPL-3.0

# Ordinary samples
define func_foo
$(shell touch vmlinux.h)
endef

define func_bar
$(call func_foo)$(shell echo y)
endef

define local_var
$(shell echo $(shell dirname ${1}) .. $(shell basename ${1}))
endef

flag-1 := $(call func_bar)
$(info flag-1 = <${flag-1}>)

flag-2 := $(call local_var,/home/rongtao)
$(info flag-2 = <${flag-2}>)

# Test recurisive define-endef
define outer_def
  define inner_def1${1}
    $$(info called inner_def1${1} $${1})
  endef
  define inner_def2${1}
    $$(info called inner_def2${1} $${1})
  endef
  define inner_tst${1}
$$(shell echo "$${1}")
  endef
endef
$(eval $(call outer_def,x))
$(call inner_def1x,aaaa)
$(call inner_def1x,bbbb)
$(call inner_def2x,cccc)
$(call inner_def2x,dddd)
ifneq ($(call inner_tstx,xxxxx),xxxxx)
  $(error outer_def->inner_tst failed)
endif

# Test target define
define add_compile_target
$(1): $(2)
	@echo "Compiling $$< -> $$@"
endef

.PHONY: build
build: test1 test2

$(eval $(call add_compile_target,test1))
$(eval $(call add_compile_target,test2))
