# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - EXPECT=[/usr/bin/expect]
# - HAVE_EXPECT=[y|n]
#
ifndef _EXPECT_MK
_EXPECT_MK = 1

include define.mk

$(call find_cmd_and_def,expect)

endif # end of _EXPECT_MK
