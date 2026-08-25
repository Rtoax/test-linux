# SPDX-License-Identifier: GPL-3.0
#
# Objects:
# - .a.o
# - .cpp.a.o
#
ifndef _TARGET_LIBA_MK
_TARGET_LIBA_MK = 1

include bits/targets.mk
include cflags.mk

CC ?= gcc
CXX ?= g++
AR ?= ar

CFLAGS_A += -fPIC
CXXFLAGS_A += -fPIC

ifdef DEBUG
  $(info CFLAGS_A = ${CFLAGS_A})
endif

$(call target_objects_append_output_prefix,${target-liba-y})
$(call add_library_objects,${target-liba-y})
$(call add_library_depends,${target-liba-y},.d)

${OUTPUT}%.a.o: %.c | ${OUTPUT}
	@$(call log_obj,${CC} A.o,$(@))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*))

${OUTPUT}%.cpp.a.o: %.cpp | ${OUTPUT}
	@$(call log_obj,${CXX} A.o,$(@))
	${Q}$(CXX) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CXXFLAGS_A) $(CXXFLAGS_A_$(*))

$(target-liba-y): %:
	@$(call log_tgt,${AR},$(@))
	${Q}${AR} rcs $(@) $(^)

endif # end of _TARGET_LIBA_MK
