# SPDX-License-Identifier: GPL-3.0

# kernel command line 'vdso=0' could disable vDSO
CMDLINE_VDSO=$(shell grep -o vdso=0 /proc/cmdline)
