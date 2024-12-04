#!/usr/bin/python
#
# dos.py
#
# eBPF adaptive packet filtering
# 1. Implementation based on eBPF
# 2. Implement kernel DOS protection, dynamically generate blacklists, and
#    count messages.
# 3. If the number of messages from the same source IP exceeds the threshold
#    within the sampling time t seconds, it is considered a DOS attack and
#    added to the blacklist.
# 4. If the number of messages from the blacklist user is less than n within
#    T minutes, remove the blacklist.
# 5. Set a whitelist, and the source IP in the whitelist is not subject to the
#    limit of 3.
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
    ./map.py -i eno1 -s 5            # Sample internal seconds
    ./map.py -i eno1 -l 10           # Sample npkts threshold
"""

parser = argparse.ArgumentParser(
    description="DOS protection",
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to track, check with ifconfig, ip, etc.")
parser.add_argument("-s", "--sample-secs", default=3,
    help="specify sampling interval seconds.")
parser.add_argument("-l", "--sample-threshold", default=100,
    help="specify sampling threshold.")

args = parser.parse_args()
ifname = args.interface
config_sample_secs = args.sample_secs
config_sample_threshold = args.sample_threshold

if ifname == "-1":
    print("Must specify interface with -i")
    exit()

flags = 0

ip = pyroute2.IPRoute()
ifidx = ip.link_lookup(ifname=ifname)[0]

# load BPF program
bpf_text = """
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
    u64 npkt;               /* total packets */
    u64 sample_start;   /* each sample interval start */
    u64 sample_npkt;        /* each sample period packets */

#define F_IN_BLACKLIST  (1 << 0)  /* this address is in blacklist */
    u32 flags;
};

BPF_ARRAY(port, uint32_t, 1);
BPF_PERCPU_ARRAY(rxcnt, long, 1);
BPF_HASH(ipv4_stat, struct ipv4_key_t, struct ipv4_stat_t);

static __always_inline int handle_ipv4(struct xdp_md *ctx, struct iphdr *iphdr)
{
    int ingress_ifindex;
    uint32_t key = 0;
    uint32_t *p_idx;
    long *value;
    struct ipv4_stat_t *stat;

    struct ipv4_stat_t newstat = {
        .npkt = 1,
        .sample_npkt = 1,
        .flags = 0,
    };

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
        u64 sec = bpf_ktime_get_ns() / 1000000000UL;

        stat = ipv4_stat.lookup(&key2);
        /**
         * Brand new source ipv4 address
         */
        if (!stat) {
            newstat.sample_start = sec;
            ipv4_stat.update(&key2, &newstat);
        /**
         * Already exist source ipv4 address
         */
        } else {
            /* In blacklist */
            if (stat->flags & F_IN_BLACKLIST) {
                stat->sample_npkt++;
                if (sec - stat->sample_start >= CONFIG_SAMPLE_SECS) {
                    if (stat->sample_npkt < CONFIG_SAMPLE_THRESHOLD) {
                        stat->flags &= ~F_IN_BLACKLIST;
                        stat->sample_npkt = 0;
                        stat->sample_start = sec;
                    }
                }
                return XDP_DROP;
            }

            stat->npkt++;
            stat->sample_npkt++;
            /**
             * One sampling, reset packets and start time.
             * Check threshold and insert to blacklist.
             */
            if (sec - stat->sample_start >= CONFIG_SAMPLE_SECS ||
                stat->sample_npkt >= CONFIG_SAMPLE_THRESHOLD) {
                stat->flags |= F_IN_BLACKLIST;
                stat->sample_npkt = 0;
                stat->sample_start = sec;
            }
        }
        return XDP_PASS;
    }

    return XDP_PASS;
}

int xdp_handler(struct xdp_md *ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;
    struct ethhdr *eth = data;
    __u16 h_proto;

    if (eth + 1 > data_end)
        return XDP_DROP;

    h_proto = eth->h_proto;

    /* Only handle ipv4 */
    if (h_proto == bpf_htons(ETH_P_IP)) {
        struct iphdr *iphdr = data + sizeof(struct ethhdr);
        if (iphdr + 1 > data_end)
            return XDP_DROP;
        return handle_ipv4(ctx, iphdr);
    } else
		return XDP_PASS;
}
"""

bpf_text = bpf_text.replace('CONFIG_SAMPLE_SECS', config_sample_secs)
bpf_text = bpf_text.replace('CONFIG_SAMPLE_THRESHOLD', config_sample_threshold)

b = BPF(text=bpf_text, cflags=["-w"])

port = b.get_table("port")
port[0] = ct.c_int(ifidx)

fn = b.load_func("xdp_handler", BPF.XDP)

b.attach_xdp(ifname, fn, flags)

rxcnt = b.get_table("rxcnt");
ipv4_stat = b.get_table("ipv4_stat");

prev = 0

print("Sampling interval %s seconds, threshold %s npkts" %
      (config_sample_secs, config_sample_threshold))
print("DOS protection of %s, hit CTRL+C to stop" % ifname)
print("%-16s %-16s %-16s %-16s %-16s %-8s" %
      ("SADDR", "SADDR_PKTS", "SAMPLE_PKTS", "SAMPLE_TIME", "ALL_PKTS", "FLAGS"))

while 1:
    try:
        val = rxcnt.sum(0).value
        if val:
            delta = val - prev
            prev = val
            #print("{} pkt/s".format(delta))
        for k, v in sorted(ipv4_stat.items(), key=lambda ipv4_stat: ipv4_stat[0].saddr):
            saddr = inet_ntop(AF_INET, pack("I", k.saddr))
            print("%-16s %-16ld %-16ld %-16ld %-16ld %-8x" %
                  (saddr, v.npkt, v.sample_npkt, v.sample_start, val, v.flags))
        time.sleep(1)
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(ifname, flags)
