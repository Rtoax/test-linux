# SPDX-License-Identifier: GPL-3.0

SIGRT_PROBE := '\#include <stdio.h>\n'
SIGRT_PROBE += '\#include <signal.h>\n'
SIGRT_PROBE += 'int main(void) {\n'
SIGRT_PROBE += '	printf("-DCONST_SIGRTMIN=%d -DCONST_SIGRTMAX=%d\\n", SIGRTMIN, SIGRTMAX);\n'
SIGRT_PROBE += '}'

SIGRT_CFLAGS := $(shell printf '%b\n' $(SIGRT_PROBE) | \
	$(CC) -xc -Wall - -o sig.out 2>&1 && ./sig.out && rm -f sig.out)

ifdef DEBUG
  $(info SIGRT_CFLAGS = ${SIGRT_CFLAGS})
endif
