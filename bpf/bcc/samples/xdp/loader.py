#!/usr/bin/python3

from bcc import BPF
import time
import sys
import argparse

examples = """examples:
    ./loader.py -i eno1       # track eno1 interface
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

b = BPF(src_file="program.c")
fn = b.load_func("myprogram", BPF.XDP)
b.attach_xdp(device, fn, 0)
packetcnt = b.get_table("packetcnt")

prev = [0] * 256
print("Printing packet counts per IP protocol-number, hit CTRL+C to stop")
print("For detach: $ sudo bpftool net detach xdp dev %s" % device)
while 1:
    try:
        for k in packetcnt.keys():
            val = packetcnt.sum(k).value
            i = k.value
            if val:
                delta = val - prev[i]
                prev[i] = val
                print("{}: {} pkt/s".format(i, delta))
        time.sleep(1)
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(device, 0)
