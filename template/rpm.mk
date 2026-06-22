# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - RPM=[/usr/bin/rpm]
# - HAVE_RPM=[y|n]
#
# - RPMBUILD=[/usr/bin/rpmbuild]
# - HAVE_RPMBUILD=[y|n]
#
ifndef _RPM_MK
_RPM_MK = 1

include define.mk

$(call find_cmd_and_def,rpm)
$(call find_cmd_and_def,rpmbuild)

endif # end of _RPM_MK
