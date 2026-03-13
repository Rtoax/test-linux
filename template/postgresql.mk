# SPDX-License-Identifier: GPL-3.0
#
# Output definitions:
# - HAVE_LIBPQ=[y|n]
# - postgresql-cflags=
#
ifndef _POSTGRESQL_MK
_POSTGRESQL_MK = 1

include define.mk

ifneq ($(wildcard /usr/include/libpq-fe.h),)
  LIBPQ_FE_H := /usr/include/libpq-fe.h
else ifneq ($(wildcard /usr/include/postgresql/libpq-fe.h),)
  LIBPQ_FE_H := /usr/include/postgresql/libpq-fe.h
  postgresql-cflags += -I/usr/include/postgresql/
endif

$(call check_file_and_def,${LIBPQ_FE_H},HAVE_LIBPQ)

export postgresql-cflags

ifdef DEBUG
  $(info postgresql-cflags = ${postgresql-cflags})
endif

endif # end of _POSTGRESQL_MK
