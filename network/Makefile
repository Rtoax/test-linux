# SPDX-License-Identifier: GPL-3.0
__USE_SOCKET_HELPERS__ = y

include helpers.mk

subdir-y := icmp
subdir-y += infiniband
subdir-y += netlink
subdir-y += nic

target-y := ethtool
target-y += tcpdump
target-y += ifconfig
target-y += ping

tcpdump-objs := ${SOCKET_HELPERS}

target-prog-y := interface.sh

LDFLAGS := -Wl,-rpath,$(shell pwd)
