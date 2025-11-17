# SPDX-License-Identifier: GPL-3.0
_TARGET_LIBA = 1

CC ?= gcc
Q ?= @

CFLAGS_A += -fPIC

ifdef DEBUG
  $(info CFLAGS_A = ${CFLAGS_A})
endif

${OUTPUT}%.a.o: %.c | ${OUTPUT}
	$(call log_obj,CC A.o,$(<),$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*))

$(target-liba-y): %:
	$(call log_exe,AR,$(<),$(@))
	${Q}ar rcs $(@) $(^)
