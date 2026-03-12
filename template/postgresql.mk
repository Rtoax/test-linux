# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_LIBPQ=[y|n]
#
ifndef _POSTGRESQL_MK
_POSTGRESQL_MK = 1

include define.mk

LIBPQ_FE_H := /usr/include/libpq-fe.h

$(call check_file_and_def,${LIBPQ_FE_H},HAVE_LIBPQ)

endif # end of _POSTGRESQL_MK
