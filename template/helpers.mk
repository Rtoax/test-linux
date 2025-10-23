# SPDX-License-Identifier: GPL-3.0
# Copyright (c) 2022-2025 Rong Tao
#
# Input definitions:
# - __USE_PROC_HELPERS__
# - __USE_SOCKET_HELPERS__
# - __USE_PTHREAD_HELPERS__
# - __USE_SCHED_HELPERS__
#
# Output definitions:
# - PROC_HELPERS
# - SOCKET_HELPERS
# - PTHREAD_HELPERS
# - SCHED_HELPERS
#
# Append definitions:
# - CFLAGS
# - LDFLAGS
#
_HELPERS = 1

ifeq (${TOPDIR},)
  $(error Not define TOPDIR, include dir.mk)
endif

define add_helper_target
  CFLAGS += -I$(shell dirname ${1})
  LDFLAGS += -Wl,-rpath,$(shell dirname ${1})
${1}:
	@make --no-print-directory --silent -C $(shell dirname ${1}) $(shell basename ${1})
endef

export PROC_HELPERS := ${TOPDIR}/fs/procfs/libproc_helpers.so
export SOCKET_HELPERS := ${TOPDIR}/ipc/socket/libsocket_helpers.so
export PTHREAD_HELPERS := ${TOPDIR}/glibc/pthread/libpthread_helpers.so
export SCHED_HELPERS := ${TOPDIR}/syscall/samples/sched/libsched_helpers.so

ifdef __USE_PROC_HELPERS__
$(eval $(call add_helper_target,${PROC_HELPERS}))
endif

ifdef __USE_SOCKET_HELPERS__
$(eval $(call add_helper_target,${SOCKET_HELPERS}))
endif

ifdef __USE_PTHREAD_HELPERS__
$(eval $(call add_helper_target,${PTHREAD_HELPERS}))
endif

ifdef __USE_SCHED_HELPERS__
$(eval $(call add_helper_target,${SCHED_HELPERS}))
endif

ifdef DEBUG
  $(info PROC_HELPERS = ${PROC_HELPERS})
  $(info SOCKET_HELPERS = ${SOCKET_HELPERS})
  $(info PTHREAD_HELPERS = ${PTHREAD_HELPERS})
  $(info SCHED_HELPERS = ${SCHED_HELPERS})
endif
