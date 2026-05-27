# SPDX-License-Identifier: GPL-3.0
include kconfig.mk

subdir-${CONFIG_UTS_NS} += uts
subdir-${CONFIG_NET_NS} += net
subdir-${CONFIG_IPC_NS} += pid
subdir-${CONFIG_IPC_NS} += ipc
subdir-${CONFIG_USER_NS} += user
subdir-y += mnt
subdir-y += syscalls
subdir-y += nsfs
subdir-y += cgroup

prog-y += info.sh
prog-y += info.sh.1

PROG_ARGS_info.sh := ps
PROG_ARGS_info.sh.1 := detail

target-y := unshare
