# SPDX-License-Identifier: GPL-3.0

VMLINUX_H ?= vmlinux.h

# $1 - struct name, like task_struct
define vmlinux_has_struct
$(shell if [[ "$$(grep -wo '^struct ${1} {' ${VMLINUX_H})" ]]; then \
		echo y; \
	else echo n; \
	fi)
endef
