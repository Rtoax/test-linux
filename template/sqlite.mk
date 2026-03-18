# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_SQLITE2=[y|n]
# - HAVE_SQLITE3=[y|n]
#
ifndef _SQLITE_MK
_SQLITE_MK = 1

include shell.mk
include define.mk

$(call check_file_and_def,/usr/include/sqlite2.h,HAVE_SQLITE2)
$(call check_file_and_def,/usr/include/sqlite3.h,HAVE_SQLITE3)

endif # end of _SQLITE_MK
