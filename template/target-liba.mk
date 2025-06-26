# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
Q ?= @

CFLAGS_A += -fPIC

${OUTPUT}%.a.o: %.c | ${OUTPUT}
	$(call log_tgt_obj,CC A.o,$(<),$(@))
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS_A) $(CFLAGS_A_$(*))

$(TARGETS_LIBA): %:
	$(call log_tgt_exe,AR,$(<),$(@))
	${Q}ar rcs $(@) $(^)
