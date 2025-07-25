# SPDX-License-Identifier: GPL-3.0
sub-dir := icmp
sub-dir += netlink
sub-dir += nic

targets := ethtool
targets += tcpdump
targets += ifconfig
targets += ping

targets-shell := interface.sh

include ../template/main.mk

socket_helpers.o: socket_helpers.h
ethtool: ethtool.o
tcpdump: tcpdump.o socket_helpers.o
ifconfig: ifconfig.o
ping: ping.o
