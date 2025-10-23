# SPDX-License-Identifier: GPL-3.0
__USE_SOCKET_HELPERS__ = y

subdir-y := icmp
subdir-y += netlink
subdir-y += nic

target-y := ethtool
target-y += tcpdump
target-y += ifconfig
target-y += ping

target-shell-y := interface.sh

LDFLAGS := -Wl,-rpath,$(shell pwd)

include ../template/main.mk

ethtool: ethtool.o
tcpdump: tcpdump.o ${SOCKET_HELPERS}
ifconfig: ifconfig.o
ping: ping.o
