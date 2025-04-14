# SPDX-License-Identifier: GPL-3.0

VMLINUX_H ?= vmlinux.h

# $1 - symbol
define vmlinux_has_sym
$(shell if [[ $$(grep -wo '${1}' ${VMLINUX_H}) ]]; then \
		echo y; \
	else echo n; \
	fi)
endef
