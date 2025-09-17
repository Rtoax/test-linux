# SPDX-License-Identifier: GPL-3.0
_TARGET_LIBSO = 1

cflags-so := -fPIC
ldflags-so := -shared -fPIC

CFLAGS_SO += ${cflags-so}
CXXFLAGS_SO += ${cflags-so}
LDFLAGS_SO += ${ldflags-so}
LDXXFLAGS_SO += ${ldflags-so}

CC_PFX := LD_LIBRARY_PATH=$(shell pwd)

ifdef DEBUG
  CFLAGS_SO += -DDEBUG=${DEBUG}
  CXXFLAGS_SO += -DDEBUG=${DEBUG}
  $(info CFLAGS_SO = ${CFLAGS_SO})
  $(info CXXFLAGS_SO = ${CXXFLAGS_SO})
  $(info targets-libso = ${targets-libso})
  $(info targets-libso-cpp = ${targets-libso-cpp})
endif

${OUTPUT}%.so.o: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC SO.o,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*))

${OUTPUT}%.cpp.so.o: %.cpp | ${OUTPUT}
	$(call log_tgt_obj,CXX SO.o,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) -c $(<) $(CXXFLAGS_SO) $(CXXFLAGS_SO_$(*))

$(targets-libso): %:
	$(call log_tgt_exe,SO,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${TEMPLATE_DIR}/targets/libso.sh multi-version $(@)

$(targets-libso-cpp): %:
	$(call log_tgt_exe,SO CPP,$(<),$(@))
	${Q}${CC_PFX} $(CXX) -o $(@) $(^) $(LDXXFLAGS_SO) $(LDXXFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${TEMPLATE_DIR}/targets/libso.sh multi-version $(@)
