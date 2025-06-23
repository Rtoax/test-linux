# SPDX-License-Identifier: GPL-3.0
sub-dir :=
sub-dir += icmp
sub-dir += netlink
sub-dir += nic

TARGETS :=
TARGETS += ethtool
TARGETS += tcpdump
TARGETS += ifconfig
TARGETS += ping

TARGETS_SHELL := interface.sh

include ../template/main.mk

ethtool: ethtool.o
tcpdump: tcpdump.o
ifconfig: ifconfig.o
ping: ping.o
