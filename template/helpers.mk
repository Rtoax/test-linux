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

define make_helper
@make --no-print-directory --silent -C ${1} ${2}
endef

PROC_HELPERS := ${TOPDIR}/fs/procfs/libproc_helpers.so
SOCKET_HELPERS := ${TOPDIR}/ipc/socket/libsocket_helpers.so
PTHREAD_HELPERS := ${TOPDIR}/glibc/pthread/libpthread_helpers.so
SCHED_HELPERS := ${TOPDIR}/syscall/samples/sched/libsched_helpers.so

ifdef __USE_PROC_HELPERS__
  CFLAGS += -I${TOPDIR}/fs/procfs/
  LDFLAGS += -Wl,-rpath,${TOPDIR}/fs/procfs/

  export PROC_HELPERS

  ${PROC_HELPERS}:
	$(call make_helper,${TOPDIR}/fs/procfs/,libproc_helpers.so)
endif

ifdef __USE_SOCKET_HELPERS__
  CFLAGS += -I${TOPDIR}/ipc/socket/
  LDFLAGS += -Wl,-rpath,${TOPDIR}/ipc/socket/

  export SOCKET_HELPERS

  ${SOCKET_HELPERS}:
	$(call make_helper,${TOPDIR}/ipc/socket/,libsocket_helpers.so)
endif

ifdef __USE_PTHREAD_HELPERS__
  CFLAGS += -I${TOPDIR}/glibc/pthread/
  LDFLAGS += -Wl,-rpath,${TOPDIR}/glibc/pthread/

  export PTHREAD_HELPERS

  ${PTHREAD_HELPERS}:
	$(call make_helper,${TOPDIR}/glibc/pthread/,libpthread_helpers.so)
endif

ifdef __USE_SCHED_HELPERS__
  CFLAGS += -I${TOPDIR}/syscall/samples/sched/
  LDFLAGS += -Wl,-rpath,${TOPDIR}/syscall/samples/sched/

  export SCHED_HELPERS

  ${SCHED_HELPERS}:
	$(call make_helper,${TOPDIR}/syscall/samples/sched/,libsched_helpers.so)
endif


ifdef DEBUG
  $(info PROC_HELPERS = ${PROC_HELPERS})
  $(info SOCKET_HELPERS = ${SOCKET_HELPERS})
  $(info PTHREAD_HELPERS = ${PTHREAD_HELPERS})
  $(info SCHED_HELPERS = ${SCHED_HELPERS})
endif
