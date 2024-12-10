#!/bin/env python
import socket
import os
from time import sleep
from pyroute2 import IPRoute
from bcc import BPF
import argparse

examples = """examples:
    ./socket_filter.py -i eno1                # track eno1 interface
"""

parser = argparse.ArgumentParser(
    description="bcc socket_filter demo",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to track, check with ifconfig, ip, etc.")

args = parser.parse_args()
interface = args.interface

if interface == "-1":
    print("Must specify interface with -i")
    exit()

b = BPF(src_file = "socket_filter.c")

f = b.load_func("socket_filter", BPF.SOCKET_FILTER)
BPF.attach_raw_socket(f, interface)
fd = f.sock
sock = socket.fromfd(fd, socket.PF_PACKET, socket.SOCK_RAW, socket.IPPROTO_IP)
sock.setblocking(True)

print("Ready");

try:
    #b.trace_print()
    while True:
        packet_str = os.read(fd, 4096)
        print("Userspace got data: {}".format(packet_str))
except KeyboardInterrupt:
    print("\nunloading")

exit()
