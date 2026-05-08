# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_CPP_MK
_TARGET_CPP_MK = 1

CXX ?= g++

include cflags.mk

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	$(call log_obj,CXX,$(@))
	${Q}$(CXX) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	$(call log_obj,CXX S,$(@))
	${Q}$(CXX) -S -o $(@) $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

# Compile .cpp to .<N>.cpp.o, this use to compile single source code to more
# than one object file.
define cpp_obj_x
$${OUTPUT}%.${1}.cpp.o: %.cpp | ${OUTPUT}
	$$(call log_obj,CXX.${1},$$(@))
	$${Q}$$(CXX) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CXXFLAGS) $$(CXXFLAGS_$$(*).${1})
endef
$(foreach i, ${SRC_SFX_LIST}, $(eval $(call cpp_obj_x,${i})))

${target-cpp-y}: %:
	$(call log_tgt,LD CXX,$(@))
	${Q}$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

$(foreach t, ${target-cpp-y}, \
  $(eval ${t}-objs := $(call append_output_prefix,${${t}-objs})) \
  $(if ${DEBUG},$(info ${t}-objs = ${${t}-objs})) \
  $(if $(shell test -f ${t}.cpp && echo yes), \
    $(eval ${t}: ${OUTPUT}${t}.cpp.o $${${t}-objs}), \
    $(eval ${t}: $${${t}-objs}) \
  ) \
  $(if ${${t}-deps}, $(eval ${t}: ${${t}-deps})) \
)

# TODO: need include ${t}-objs .d file
$(foreach t, ${target-cpp-y}, \
  $(if $(shell test -f ${OUTPUT}${t}.cpp.o.d && echo yes), \
    $(if ${DEBUG}, $(info Found ${OUTPUT}${t}.cpp.o.d)) \
    $(eval include ${OUTPUT}${t}.cpp.o.d), \
    $(if ${DEBUG}, $(info Not found ${OUTPUT}${t}.cpp.o.d)) \
  ) \
)

endif
