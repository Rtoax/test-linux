# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - PHP=[/usr/bin/php]
# - HAVE_PHP=[y|n]
#
ifndef _PHP_MK
_PHP_MK = 1

include define.mk

$(call find_cmd_and_def,php)

endif # end of _PHP_MK
