# SPDX-License-Identifier: GPL-3.0

pound := \#

# Probe printf(3) with non-output gcc command
PRINTF_PROBE := '$(pound)include <stdio.h>\n'
PRINTF_PROBE += 'int main(void) {\n'
PRINTF_PROBE += '	printf("hello\\n");\n'
PRINTF_PROBE += '}'
define probe_libc_printf
  $(shell printf '%b\n' $(PRINTF_PROBE) | \
    $(CC) -x c -Wall - $(1) -S -o - >/dev/null 2>&1 \
      && echo 1)
endef
