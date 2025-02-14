# SPDX-License-Identifier: GPL-3.0

Q ?= @
BPFTOOL ?= bpftool

vmlinux.h:
	@echo -e "  BPFTOOL  \033[1;32m$(@)\033[m"
	${Q}${BPFTOOL} btf dump file /sys/kernel/btf/vmlinux format c > vmlinux.h

