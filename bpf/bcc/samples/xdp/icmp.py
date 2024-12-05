#!/usr/bin/python3

from bcc import BPF
import time
import sys
import argparse
import socket
from pyroute2 import IPRoute

examples = """examples:
    ./icmp.py -i eno1                # track eno1 interface
    ./icmp.py -i eno1 -t tc          # drop icmp
    ./icmp.py -i eno1 -t tc_drop     # drop all packets
    ./icmp.py -i eno1 -t tc_pingpong # drop nothing
"""

parser = argparse.ArgumentParser(
    description="bcc XDP demo",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to track, check with ifconfig, ip, etc.")
parser.add_argument("-t", "--tc", default="-1",
    help="specify a traffix control. tc, tc_drop, tc_pingpong")

args = parser.parse_args()
device = args.interface
tc = args.tc

if device == "-1":
    print("Must specify interface with -i")
    exit()

global iproute
iproute = IPRoute()
links = iproute.link_lookup(ifname=device)
if not links:
    print("ERROR: Not exist nic interface %s!!" % device)
    exit()
idx = links[0]

b = BPF(src_file="icmp.c")
fn = b.load_func("xdp_icmp", BPF.XDP)
b.attach_xdp(device, fn, 0)

if tc == "-1":
    print("You can specify -t,--tc")
elif tc == "tc" or tc == "tc_drop" or tc == "tc_pingpong":
    # BPF_PROG_TYPE_SCHED_CLS
    fi = b.load_func(tc, BPF.SCHED_CLS)

    try:
        iproute.tc("add", "ingress", idx, "ffff:")
    except:
        print("qdisc ingress alread exists")

    iproute.tc("add-filter", "bpf", idx, ":1", fd=fi.fd, name=fi.name,
                parent="ffff:", action="drop", classid=1)
else:
    print("ERROR: Unknow -t argument")
    exit()

print("Tracing ICMP, hit CTRL+C to stop")
while 1:
    try:
        b.trace_print()
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(device, 0)
if tc != "-1":
    iproute.tc("del", "ingress", idx, "ffff:")
