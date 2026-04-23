# SPDX-License-Identifier: GPL-3.0
ifndef _TARGET_LIBSO_MK
_TARGET_LIBSO_MK = 1

cflags-so := -fPIC
ldflags-so := -shared -fPIC

CFLAGS_SO += ${cflags-so}
CXXFLAGS_SO += ${cflags-so}
LDFLAGS_SO += ${ldflags-so}
LDXXFLAGS_SO += ${ldflags-so}

include cflags.mk
include dir.mk

LIBSO_SH := ${TOPDIR}/scripts/libso-multiver.sh

ifdef DEBUG
  LIBSO_SH += --verbose
  $(info CFLAGS_SO = ${CFLAGS_SO})
  $(info CXXFLAGS_SO = ${CXXFLAGS_SO})
  $(info target-libso-y = ${target-libso-y})
  $(info target-libso-cpp-y = ${target-libso-cpp-y})
endif

# append ${OUTPUT} for each object
$(foreach so, ${target-libso-y} ${target-libso-cpp-y}, \
  $(eval ${so}-objs := $(call append_output_prefix,${${so}-objs})) \
  $(if ${DEBUG},$(info ${so}-objs = ${${so}-objs})) \
)

$(foreach lib, ${target-libso-y} ${target-libso-cpp-y}, $(eval ${lib}: $${${lib}-objs}))

${OUTPUT}%.so.o: %.c | ${OUTPUT}
	$(call log_obj,CC SO.o,$(@))
	$(shell mkdir -p $(shell dirname $(@)))
	${Q}$(CC) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*))

${OUTPUT}%.cpp.so.o: %.cpp | ${OUTPUT}
	$(call log_obj,CXX SO.o,$(@))
	$(shell mkdir -p $(shell dirname $(@)))
	${Q}$(CXX) -MMD -MT $(@) -MF $(@:=.d) -o $(@) -c $(<) $(CXXFLAGS_SO) $(CXXFLAGS_SO_$(*))

# All symlinks depends on original dynamic target, thus, if some one need the
# symlinks, the dynamic library will be compiled.
$(foreach so, ${target-libso-y} ${target-libso-cpp-y}, \
  $(if $(shell ${LIBSO_SH} symlinks-names ${so}), \
    $(eval $(shell ${LIBSO_SH} symlinks-names ${so}): ${so} ;)\
  ) \
)

$(target-libso-y): %:
	$(call log_tgt,SO,$(@))
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${LIBSO_SH} multi-version $(@)

$(target-libso-cpp-y): %:
	$(call log_tgt,SO CPP,$(@))
	${Q}$(CXX) -o $(@) $(^) $(LDXXFLAGS_SO) $(LDXXFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${LIBSO_SH} multi-version $(@)

$(foreach so, ${target-libso-y} ${target-libso-cpp-y}, \
  $(foreach obj, ${${so}-objs}, \
    $(if $(shell test -f ${obj}.d && echo yes), \
      $(if ${DEBUG}, $(info Include ${obj}.d)) \
      $(eval include ${obj}.d), \
      $(if ${DEBUG}, $(info Not found ${obj}.d)) \
    ) \
  ) \
  $(if ${${so}-deps}, $(eval ${so}: ${${so}-deps})) \
)

endif
