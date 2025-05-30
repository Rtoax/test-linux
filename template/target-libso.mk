# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
Q ?= @

%.so.o: %.c
	@echo -e "  CC SO.O \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS_SO) $(CFLAGS_SO_$(*))

$(TARGETS_LIBSO): %:
	@echo -e "  SO  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS_SO) $(LDFLAGS_SO_$(*)) -Wl,-soname=$(@)
