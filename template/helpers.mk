# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao
#
# Note: _helpers.{c,h} better not use symlinks, you could check with:
#
#   $ find -name '*_helpers.c' -exec basename {} \; | sort
#
# Input definitions:
# - __USE_PROC_HELPERS__=y
# - __USE_SOCKET_HELPERS__=y
# - __USE_PTHREAD_HELPERS__=y
# - __USE_SCHED_HELPERS__=y
# - __USE_MMAP_HELPERS__=y
#
# Output definitions:
# - PROC_HELPERS
# - SOCKET_HELPERS
# - PTHREAD_HELPERS
# - SCHED_HELPERS
# - MMAP_HELPERS
#
# Append definitions:
# - CFLAGS
# - LDFLAGS
#
_HELPERS = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

# $1 - helper library absolute path
# $2 - turn on with 'y', otherwise turn off
define add_helper_target
ifeq ($(2),y)
  CFLAGS += -I$(shell dirname ${1})
  LDFLAGS += -Wl,-rpath,$(shell dirname ${1})
endif
${1}:
	@make --no-print-directory --silent -C $(shell dirname ${1}) $(shell basename ${1})
endef

export PROC_HELPERS := ${TOPDIR}/fs/procfs/libproc_helpers.so
export SOCKET_HELPERS := ${TOPDIR}/ipc/socket/libsocket_helpers.so
export PTHREAD_HELPERS := ${TOPDIR}/glibc/pthread/libpthread_helpers.so
export SCHED_HELPERS := ${TOPDIR}/syscall/samples/sched/libsched_helpers.so
export MMAP_HELPERS := ${TOPDIR}/syscall/samples/mm/mmap/libmmap_helpers.so

$(eval $(call add_helper_target,${PROC_HELPERS},${__USE_PROC_HELPERS__}))
$(eval $(call add_helper_target,${SOCKET_HELPERS},${__USE_SOCKET_HELPERS__}))
$(eval $(call add_helper_target,${PTHREAD_HELPERS},${__USE_PTHREAD_HELPERS__}))
$(eval $(call add_helper_target,${SCHED_HELPERS},${__USE_SCHED_HELPERS__}))
$(eval $(call add_helper_target,${MMAP_HELPERS},${__USE_MMAP_HELPERS__}))

ifdef DEBUG
  $(info PROC_HELPERS = ${PROC_HELPERS})
  $(info SOCKET_HELPERS = ${SOCKET_HELPERS})
  $(info PTHREAD_HELPERS = ${PTHREAD_HELPERS})
  $(info SCHED_HELPERS = ${SCHED_HELPERS})
  $(info MMAP_HELPERS = ${MMAP_HELPERS})
endif
