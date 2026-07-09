# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_CPP_MK
_TARGET_CPP_MK = 1

CXX ?= g++

include bits/targets.mk
include cflags.mk

${OUTPUT}%.cpp.o: %.cpp | ${OUTPUT}
	$(call log_obj,${CXX},$(@))
	${Q}$(CXX) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	$(call log_obj,${CXX} S,$(@))
	${Q}$(CXX) -S -o $(@) $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

# Compile .cpp to .<N>.cpp.o, this use to compile single source code to more
# than one object file.
define cpp_obj_x
$${OUTPUT}%.${1}.cpp.o: %.cpp | ${OUTPUT}
	$$(call log_obj,${CXX},$$(@))
	$${Q}$$(CXX) -MMD -MT $$(@) -MF $$(@:=.d) -o $$(@) -c $$(<) $$(CXXFLAGS) $$(CXXFLAGS_$$(*).${1})
endef
$(foreach i, ${SRC_SFX_LIST}, $(eval $(call cpp_obj_x,${i})))

${target-cpp-y}: %:
	$(call log_tgt,${CXX} LD,$(@))
	${Q}$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))

$(call target_objects_append_output_prefix,${target-cpp-y})
$(call add_target_objects,.cpp,.cpp.o,${target-cpp-y})
$(call add_target_depends,${target-cpp-y},.cpp.o.d,.d)

endif
