#!/usr/bin/python
#
# map.py
#
from bcc import BPF
import pyroute2
import time
import sys
import ctypes as ct

flags = 0
def usage():
    print("Usage: {0} <ifdev>".format(sys.argv[0]))
    print("e.g.: {0} eth0\n".format(sys.argv[0]))
    exit(1)

if len(sys.argv) != 2:
    usage()

ifname = sys.argv[1]

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

BPF_ARRAY(port, uint32_t, 1);
BPF_PERCPU_ARRAY(rxcnt, long, 1);

static __always_inline int handle_ipv4(struct xdp_md *ctx)
{
    int ingress_ifindex;
    uint32_t key = 0;
    uint32_t *p_idx;
    long *value;

    /* rxq->dev->ifindex */
    ingress_ifindex = ctx->ingress_ifindex;

    p_idx = port.lookup(&key);
    if (!p_idx)
        return XDP_PASS;

    if (*p_idx == ingress_ifindex) {
        value = rxcnt.lookup(&key);
        if (value)
            *value += 1;
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
prev = 0
print("Drop packets of %s, hit CTRL+C to stop" % ifname)
while 1:
    try:
        val = rxcnt.sum(0).value
        if val:
            delta = val - prev
            prev = val
            print("{} pkt/s".format(delta))
        time.sleep(1)
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(ifname, flags)
