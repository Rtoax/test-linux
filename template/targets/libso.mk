# SPDX-License-Identifier: GPL-3.0
_TARGET_LIBSO = 1

cflags-so := -fPIC
ldflags-so := -shared -fPIC

CFLAGS_SO += ${cflags-so}
CXXFLAGS_SO += ${cflags-so}
LDFLAGS_SO += ${ldflags-so}
LDXXFLAGS_SO += ${ldflags-so}

ifdef DEBUG
  CFLAGS_SO += -DDEBUG=${DEBUG}
  CXXFLAGS_SO += -DDEBUG=${DEBUG}
  $(info CFLAGS_SO = ${CFLAGS_SO})
  $(info CXXFLAGS_SO = ${CXXFLAGS_SO})
  $(info target-libso-y = ${target-libso-y})
  $(info target-libso-cpp-y = ${target-libso-cpp-y})
endif

LIBSO := ${TEMPLATE_DIR}/targets/libso.sh

${OUTPUT}%.so.o: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC SO.o,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*))

${OUTPUT}%.cpp.so.o: %.cpp | ${OUTPUT}
	$(call log_tgt_obj,CXX SO.o,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) -c $(<) $(CXXFLAGS_SO) $(CXXFLAGS_SO_$(*))

# All symlinks depends on original dynamic target, thus, if some one need the
# symlinks, the dynamic library will be compiled.
$(foreach so,${target-libso-y},	\
$(if $(shell ${LIBSO} symlinks-names ${so}),	\
$(eval $(shell ${LIBSO} symlinks-names ${so}): ${so}	;)	\
)	\
)

$(target-libso-y): %:
	$(call log_tgt_exe,SO,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${LIBSO} multi-version $(@)

$(target-libso-cpp-y): %:
	$(call log_tgt_exe,SO CPP,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) $(^) $(LDXXFLAGS_SO) $(LDXXFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${LIBSO} multi-version $(@)
