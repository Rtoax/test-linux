#!/usr/bin/python3

from bcc import BPF
import time
import sys
import argparse

examples = """examples:
    ./icmp.py -i eno1       # track eno1 interface
"""

parser = argparse.ArgumentParser(
    description="bcc XDP demo",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to track, check with ifconfig, ip, etc.")

args = parser.parse_args()
device = args.interface

if device == "-1":
    print("Must specify interface with -i")
    exit()

b = BPF(src_file="icmp.c")
fn = b.load_func("xdp_icmp", BPF.XDP)
b.attach_xdp(device, fn, 0)

print("Tracing ICMP, hit CTRL+C to stop")
while 1:
    try:
        b.trace_print()
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(device, 0)
