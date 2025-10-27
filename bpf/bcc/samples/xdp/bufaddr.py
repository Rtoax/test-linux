#!/usr/bin/python
# @lint-avoid-python-3-compatibility-imports
#
# bufaddr.py - Get buffer address
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 27-Oct-2025   Rong Tao    Create this.
#
from bcc import BPF
from bcc.utils import printb
import pyroute2
import time
import sys
import ctypes as ct
import argparse
import struct
from socket import inet_aton, inet_ntop, AF_INET, AF_INET6

description = """eBPF adaptive packet filtering

"""

examples = """examples:
  ./bufaddr.py -i eno1                      # Handle eno1 interface
"""

parser = argparse.ArgumentParser(
    description=description,
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to protection, check with ifconfig, ip addr, etc.")

args = parser.parse_args()
ifname = args.interface


if ifname == "-1":
    print("Must specify interface with -i")
    exit()

flags = 0

ip = pyroute2.IPRoute()
ifidx_a = ip.link_lookup(ifname=ifname)
if not ifidx_a:
    print("ERROR: Not exist nic interface %s!!" % ifname)
    exit()

ifidx = ifidx_a[0]

bpf_text = """
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/if_ether.h>

struct event_t {
    u64 bufaddr;
};

BPF_RINGBUF_OUTPUT(output, 1);

int xdp_handler(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    struct event_t event = {};

    if (eth + 1 > data_end)
        return XDP_PASS;

    event.bufaddr = (u64)data;
    output.ringbuf_output(&event, sizeof(event), 0);

    return XDP_PASS;
}
"""

# load BPF program
b = BPF(text=bpf_text, cflags=["-w"])
fn = b.load_func("xdp_handler", BPF.XDP)
b.attach_xdp(ifname, fn, flags)

def print_event(cpu, data, size):
    data = b["output"].event(data)
    printb(b"bufaddr 0x%lx" % data.bufaddr)

b["output"].open_ring_buffer(print_event)
while True:
    b.ring_buffer_poll()

b.remove_xdp(ifname, flags)
