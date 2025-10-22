# SPDX-License-Identifier: GPL-3.0
subdir-y := icmp
subdir-y += netlink
subdir-y += nic

target-y := ethtool
target-y += tcpdump
target-y += ifconfig
target-y += ping

target-shell-y := interface.sh

include ../template/main.mk

socket_helpers.o: socket_helpers.h
ethtool: ethtool.o
tcpdump: tcpdump.o socket_helpers.o
ifconfig: ifconfig.o
ping: ping.o
