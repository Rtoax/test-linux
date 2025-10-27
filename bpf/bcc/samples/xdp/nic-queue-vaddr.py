#!/usr/bin/python
# @lint-avoid-python-3-compatibility-imports
#
# nic-queue-vaddr.py - Get NIC queue memory buffer address for each pkt with XDP.
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 27-Oct-2025   Rong Tao    Create this.
#
from bcc import BPF
from bcc.utils import printb
import time
import sys
import ctypes as ct
import argparse
import struct
from socket import inet_aton, inet_ntop, AF_INET, AF_INET6

description = """eBPF NIC queue memory address dump.
"""

examples = """examples:
  $ sudo ./nic-queue-vaddr.py -i eno1                      # Handle eno1 interface
  buf: addr 0xffff004679ec0100, ....

  # Then, you could use crash's kmem check the memory address information

    crash> kmem 0xffff004679ec0100
    NODE
      1
    ZONE  NAME        SIZE    FREE      MEM_MAP       START_PADDR  START_MAPNR
      2   Normal    1572864   92439  ffffffc010000000   4000000000       0
    AREA    SIZE  FREE_AREA_STRUCT
      7    8192k  ffff0057ffff72a8
    ffffffc0119e6000  (ffff004679ec0100 is 109th of 128 pages)
"""

parser = argparse.ArgumentParser(
    description=description,
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to track, check with ifconfig, ip addr, etc.")

args = parser.parse_args()
ifname = args.interface


if ifname == "-1":
    print("Must specify interface with -i")
    exit()

flags = 0

if not ifname:
    print("ERROR: Not set nic interface %s!!" % ifname)
    exit()

bpf_text = """
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/if_ether.h>

struct event_t {
    u64 bufaddr;
    u64 buflen;
    int h_proto;
    int ip_proto;
};

#ifndef ETH_P_IP
#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/
#endif

BPF_RINGBUF_OUTPUT(output, 1);

int xdp_handler(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
	struct iphdr *iphdr;
    struct event_t event = {};

    if ((void *)(eth + 1) > data_end)
        return XDP_PASS;

    event.bufaddr = (u64)data;
    event.buflen = (unsigned long)(data_end - data);
    event.h_proto = eth->h_proto;

    if (eth->h_proto == bpf_htons(ETH_P_IP)) {
        iphdr = data + sizeof(struct ethhdr);
        if ((void *)(iphdr + 1) > data_end)
            return XDP_PASS;
	    event.ip_proto = iphdr->protocol;
    } else {
	    event.ip_proto = -1;
    }

    /**
     * Could not call virt_to_phys() in xdp prog, you should use crash's kmem
     * to get memory information of bufaddr, not in XDP prog.
     */

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
    printb(b"buf: addr 0x%lx, len 0x%lx, eth proto %d, ip proto %d" %
           (data.bufaddr, data.buflen, data.h_proto, data.ip_proto))

b["output"].open_ring_buffer(print_event)
while True:
    try:
        b.ring_buffer_poll()
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(ifname, flags)
