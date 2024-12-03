#!/usr/bin/python
#
# map.py
#
from bcc import BPF
import pyroute2
import time
import sys
import ctypes as ct
import argparse
from struct import pack
from socket import inet_ntop, AF_INET, AF_INET6

examples = """examples:
    ./map.py -i eno1                 # Handle eno1 interface
"""

parser = argparse.ArgumentParser(
    description="bcc XDP test",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to track, check with ifconfig, ip, etc.")

args = parser.parse_args()
ifname = args.interface

if ifname == "-1":
    print("Must specify interface with -i")
    exit()

flags = 0

ip = pyroute2.IPRoute()
ifidx = ip.link_lookup(ifname=ifname)[0]

# load BPF program
b = BPF(text = """
#include <uapi/linux/bpf.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/if_ether.h>

#ifndef ETH_P_IP
#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/
#endif

struct ipv4_key_t {
    u32 saddr;
};
struct ipv4_stat_t {
    u64 npkt;   // statistic
};

BPF_ARRAY(port, uint32_t, 1);
BPF_PERCPU_ARRAY(rxcnt, long, 1);
BPF_HASH(ipv4_stat, struct ipv4_key_t, struct ipv4_stat_t);

static __always_inline int handle_ipv4(struct xdp_md *ctx)
{
    int ingress_ifindex;
    uint32_t key = 0;
    uint32_t *p_idx;
    long *value;
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    struct iphdr *iphdr = data + sizeof(struct ethhdr);
    struct ipv4_stat_t *stat;
    struct ipv4_stat_t newstat = {
        .npkt = 1,
    };
    if (iphdr + 1 > data_end)
        return XDP_DROP;

    struct ipv4_key_t key2 = {
        .saddr = iphdr->saddr,
    };

    /* rxq->dev->ifindex */
    ingress_ifindex = ctx->ingress_ifindex;

    p_idx = port.lookup(&key);
    if (!p_idx)
        return XDP_PASS;

    if (*p_idx == ingress_ifindex) {
        value = rxcnt.lookup(&key);
        if (value)
            *value += 1;
        stat = ipv4_stat.lookup(&key2);
        if (!stat) {
            ipv4_stat.update(&key2, &newstat);
        } else {
            stat->npkt++;
        }
        return XDP_DROP;
    }

    return XDP_PASS;
}

int xdp_drop(struct xdp_md *ctx) {
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    __u16 h_proto;

    if (eth + 1 > data_end)
        return XDP_DROP;

    h_proto = eth->h_proto;

    /* Only handle ipv4 */
    if (h_proto == bpf_htons(ETH_P_IP))
        return handle_ipv4(ctx);
    else
		return XDP_PASS;
}
""", cflags=["-w"])

port = b.get_table("port")
port[0] = ct.c_int(ifidx)

fn = b.load_func("xdp_drop", BPF.XDP)

b.attach_xdp(ifname, fn, flags)

rxcnt = b.get_table("rxcnt");
ipv4_stat = b.get_table("ipv4_stat");
prev = 0
print("Drop packets of %s, hit CTRL+C to stop" % ifname)
while 1:
    try:
        val = rxcnt.sum(0).value
        if val:
            delta = val - prev
            prev = val
            print("{} pkt/s".format(delta))
        for k, v in sorted(ipv4_stat.items(), key=lambda ipv4_stat: ipv4_stat[0]):
            saddr = inet_ntop(AF_INET, pack("I", k.saddr))
            print("%-16s %-16ld" % (saddr, v.npkt))
        time.sleep(1)
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(ifname, flags)
