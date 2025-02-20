# SPDX-License-Identifier: GPL-3.0

SIGNAL_PROBE := '\#include <stdio.h>\n'
SIGNAL_PROBE += '\#include <signal.h>\n'
SIGNAL_PROBE += 'int main(void) {\n'
SIGNAL_PROBE += '	printf("-DCONST_SIGRTMIN=%d -DCONST_SIGRTMAX=%d\\n", SIGRTMIN, SIGRTMAX);\n'
SIGNAL_PROBE += '}'

SIGNAL_CFLAGS := $(shell printf '%b\n' $(SIGNAL_PROBE) | \
	$(CC) -xc -Wall - -o sig.out 2>&1 && ./sig.out && rm -f sig.out)

$(info SIGNAL_CFLAGS = ${SIGNAL_CFLAGS})
