# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
Q ?= @

%.a.o: %.c
	@echo -e "  CC A.O  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*)) -fPIC

$(TARGETS_LIBA): %:
	@echo -e "  AR  \033[1;32m$(^) to $(@)\033[m"
	${Q}ar rcs $(@) $(^)
