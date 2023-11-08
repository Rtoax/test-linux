#!/bin/env python
import socket
import os
from time import sleep
from pyroute2 import IPRoute
from bcc import BPF

interface = "eno1"

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
except KeyboardInterrypt:
    print("\n unloading")

exit()
