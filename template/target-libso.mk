# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
Q ?= @

CFLAGS_SO += -fPIC
LDFLAGS_SO += -shared -fPIC

CC_PFX := LD_LIBRARY_PATH=$(shell pwd)

${OUTPUT}%.so.o: %.c | ${OUTPUT}
	@echo -e "  CC SO.O \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}${CC_PFX} $(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*))

$(TARGETS_LIBSO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}${CC_PFX} $(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_SO_$(*)) -Wl,-soname=$(@)
