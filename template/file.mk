# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2022-2026 Rong Tao
#
# Export functions:
# - reset_file($file): rename file to file.old
#
_FILE_MK = 1

include shell.mk

# $1: filename
define reset_file
	function __reset_file() { \
		if [[ -e $${1} ]]; then \
			if [[ -e $${1}.old ]]; then \
				__reset_file $${1}.old; \
			fi; \
			mv $${1} $${1}.old; \
		fi; \
	}; \
	__reset_file $1
endef
