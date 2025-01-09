#!/bin/bash
#
# 0 Echo Reply
# 3 Destination Unreachable
# 4 Source Quench
# 5 Redirect
# 8 Echo
# 11 Time Exceeded

ifname=any

# filter all ICMPv4 or ICMPv6 packets
sudo tcpdump -i ${ifname} icmp
sudo tcpdump -i ${ifname} icmp6

# filter ICMP echo-reply or echo-requests
sudo tcpdump -i ${ifname} "icmp[0] == 0"
sudo tcpdump -i ${ifname} "icmp[0] == 8"
sudo tcpdump -i ${ifname} "icmp[0] == 0 || icmp[0] == 8"
