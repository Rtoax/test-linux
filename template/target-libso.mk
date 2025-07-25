# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
Q ?= @

CFLAGS_SO += -fPIC
LDFLAGS_SO += -shared -fPIC

CC_PFX := LD_LIBRARY_PATH=$(shell pwd)

${OUTPUT}%.so.o: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC SO.o,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*))

$(targets-libso): %:
	$(call log_tgt_exe,SO,$(<),$(@))
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_SO_$(*)) -Wl,-soname=$(@)
	${Q}${SHELL} ${TEMPLATE_DIR}/target-libso.sh multi-version $(@)
