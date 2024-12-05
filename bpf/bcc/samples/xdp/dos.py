#!/usr/bin/python
# @lint-avoid-python-3-compatibility-imports
#
# dos.py - eBPF adaptive packet filtering for DoS attack
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 04-Dec-2024   Rong Tao    Create this.
# 05-Dec-2024   Rong Tao    Support specify blacklist and whitelist.
#
from bcc import BPF
import pyroute2
import time
import sys
import ctypes as ct
import argparse
import struct
from socket import inet_aton, inet_ntop, AF_INET, AF_INET6

description = """eBPF adaptive packet filtering

  1. Implementation based on eBPF
  2. Implement kernel DOS protection, dynamically generate blacklists, and
     count messages.
  3. If the number of messages from the same source IP exceeds the threshold '\033[1;32mn\033[m'
     within the sampling time '\033[1;32mt\033[m' seconds, it is considered a DOS attack and
     added to the blacklist.
  4. If the number of messages from the blacklist user is less than '\033[1;32mN\033[m' within
     '\033[1;32mT\033[m' minutes, remove the blacklist.
  5. Set a whitelist, and the source IP in the whitelist is not subject to the
     limit of 3.
"""

examples = """examples:
  ./dos.py -i eno1                      # Handle eno1 interface
  ./dos.py -i eno1 -t 5                 # Sample interval seconds, see 't' above
  ./dos.py -i eno1 -n 10                # Sample npkts threshold, see 'n' above
  ./dos.py -i eno1 -T 5                 # Sample interval seconds in blacklist, see 'T' above
  ./dos.py -i eno1 -N 10                # Sample npkts threshold in blacklist, see 'N' above
  ./dos.py -i eno1 -W 192.168.30.179    # Specify white address
  ./dos.py -i eno1 -B 192.168.30.179    # Specify black address

  ./dos.py -i enp11s0 -t 10 -n 20 -T 20 -N 30 -W 192.168.30.179 192.168.30.180 -B 192.168.30.1

"""

parser = argparse.ArgumentParser(
    description=description,
    formatter_class=argparse.RawDescriptionHelpFormatter,
    epilog=examples)
parser.add_argument("-i", "--interface", default="-1",
    help="specify ether interface to protection, check with ifconfig, ip addr, etc.")
parser.add_argument("-t", "--sample-secs", default=3,
    help="specify sampling interval seconds, use to insert to blacklist, see 't' in description.")
parser.add_argument("-n", "--sample-threshold", default=100,
    help="specify sampling threshold, use to insert to blacklist, see 'n' in description.")
parser.add_argument("-T", "--blacklist-sample-secs", default=3,
    help="specify sampling interval seconds in blacklist, use to remove from blacklist, see 'T' in description.")
parser.add_argument("-N", "--blacklist-sample-threshold", default=100,
    help="specify sampling threshold in blacklist, use to remove from blacklist, see 'N' in description.")
parser.add_argument("-W", "--whitelist", nargs='*',
    help="specify the address white list, (may be listed multiple times).")
parser.add_argument("-B", "--blacklist", nargs='*',
    help="specify the address black list, (may be listed multiple times).")

args = parser.parse_args()
ifname = args.interface
config_sample_secs = args.sample_secs
config_sample_threshold = args.sample_threshold
config_blacklist_sample_secs = args.blacklist_sample_secs
config_blacklist_sample_threshold = args.blacklist_sample_threshold
config_whitelist = args.whitelist
config_blacklist = args.blacklist


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
    u64 npkt;               /* total packets of one source address */
    u64 sample_start;       /* each sample interval start, both used in
                               whitelist and blacklist */
    u64 sample_npkt;        /* each sample period packets count, both used
                               in whitelist and blacklist */

#define F_IN_BLACKLIST  (1 << 0)  /* address in blacklist */
#define F_IN_WHITELIST  (1 << 1)  /* address in whitelist */
#define F_BLACK_FOREVER (1 << 2)  /* address in blacklist forever */
    u32 flags;
};

BPF_HASH(ipv4_whitelist, u32, int);
BPF_HASH(ipv4_blacklist, u32, int);
BPF_HASH(ipv4_stat, struct ipv4_key_t, struct ipv4_stat_t);

static __always_inline int handle_ipv4(struct xdp_md *ctx, struct iphdr *iphdr)
{
    uint32_t if_index = CONFIG_IF_INDEX;
    struct ipv4_stat_t *stat;
    u64 delta_s;
    u64 sec = bpf_ktime_get_ns() / 1000000000UL;

    struct ipv4_key_t key_saddr = {
        .saddr = iphdr->saddr,
    };

    struct ipv4_stat_t newstat = {
        .npkt = 0,
        .sample_npkt = 0,
        .flags = 0,
    };

    /**
     * FIXME: Ignore loopback??
     */
    if (iphdr->saddr == 0)
        return XDP_PASS;

    /* rxq->dev->ifindex */
    if (if_index != ctx->ingress_ifindex)
        return XDP_PASS;

    stat = ipv4_stat.lookup(&key_saddr);
    /**
     * Brand new source ipv4 address
     */
    if (!stat) {
        int *white = ipv4_whitelist.lookup(&iphdr->saddr);
        if (white)
            newstat.flags |= F_IN_WHITELIST;
        int *black = ipv4_blacklist.lookup(&iphdr->saddr);
        if (black)
            newstat.flags |= F_BLACK_FOREVER;
        newstat.sample_start = sec;
        newstat.npkt++;
        ipv4_stat.update(&key_saddr, &newstat);
        if (newstat.flags & F_BLACK_FOREVER)
            return XDP_DROP;
        return XDP_PASS;
    }

    stat->npkt++;
    stat->sample_npkt++;

    if (stat->flags & F_BLACK_FOREVER)
        return XDP_DROP;

    /**
     * Already exist source ipv4 address
     */

    /* In blacklist and not in whitelist */
    if (stat->flags & F_IN_BLACKLIST && !(stat->flags & F_IN_WHITELIST)) {
        /**
         * If it is greater than the threshold, the time and number of packets
         * should be updated in real time.
         */
        if (stat->sample_npkt >= CONFIG_BLACKLIST_SAMPLE_THRESHOLD) {
            stat->sample_npkt = 0;
            stat->sample_start = sec;
        }

        if (sec - stat->sample_start >= CONFIG_BLACKLIST_SAMPLE_SECS &&
            stat->sample_npkt < CONFIG_BLACKLIST_SAMPLE_THRESHOLD) {
            /* Remove from blacklist */
            stat->flags &= ~F_IN_BLACKLIST;
            stat->sample_npkt = 0;
            stat->sample_start = sec;
        }
        return XDP_DROP;
    }

    delta_s = sec - stat->sample_start;

    /**
     * One sampling, check threshold and insert to blacklist.
     */
    if ((delta_s <= CONFIG_SAMPLE_SECS && stat->sample_npkt >= CONFIG_SAMPLE_THRESHOLD) ||
        (delta_s > CONFIG_SAMPLE_SECS && stat->sample_npkt >= CONFIG_SAMPLE_THRESHOLD)) {

        /* Never add address in whitelist to blacklist */
        if (!(stat->flags & F_IN_WHITELIST))
            stat->flags |= F_IN_BLACKLIST;

        stat->sample_npkt = 0;
        stat->sample_start = sec;

    /* Packet rate is OK, reset sampling */
    } else if (delta_s > CONFIG_SAMPLE_SECS && stat->sample_npkt < CONFIG_SAMPLE_THRESHOLD) {
        stat->sample_npkt = 0;
        stat->sample_start = sec;
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

ADDR_FLAGS = [
    ('\033[1;31mBLACK\033[m', (1 << 0)),
    ('\033[1;37mWHITE\033[m', (1 << 1)),
    ('\033[1;31mBLACK_FOREVER\033[m', (1 << 2)),
]

def _decode_flags(flags, flag_list):
    str_flags = []
    for flag, bit in flag_list:
        if flags & bit:
            str_flags.append(flag)
        flags &= ~bit
    if flags or not str_flags:
        str_flags.append('0x{:x}'.format(flags))
    return str_flags

def decode_addr_flags(flags):
    str_flags = []
    str_flags.extend(_decode_flags(flags, ADDR_FLAGS))
    return '|'.join(str_flags)

bpf_text = bpf_text.replace('CONFIG_IF_INDEX', str(ifidx))
bpf_text = bpf_text.replace('CONFIG_SAMPLE_SECS', str(config_sample_secs))
bpf_text = bpf_text.replace('CONFIG_SAMPLE_THRESHOLD', str(config_sample_threshold))
bpf_text = bpf_text.replace('CONFIG_BLACKLIST_SAMPLE_SECS', str(config_blacklist_sample_secs))
bpf_text = bpf_text.replace('CONFIG_BLACKLIST_SAMPLE_THRESHOLD', str(config_blacklist_sample_threshold))

b = BPF(text=bpf_text, cflags=["-w"])

fn = b.load_func("xdp_handler", BPF.XDP)

ipv4_whitelist = b.get_table("ipv4_whitelist");
ipv4_blacklist = b.get_table("ipv4_blacklist");
ipv4_stat = b.get_table("ipv4_stat");

if config_whitelist:
    for white_ip_str in config_whitelist:
        print(f"Add {white_ip_str} to whitelist")
        ipnum = struct.unpack("i", inet_aton(white_ip_str))[0]
        ipv4_whitelist.__setitem__(ct.c_uint32(ipnum), ct.c_int(1));

if config_blacklist:
    for black_ip_str in config_blacklist:
        print(f"Add {black_ip_str} to blacklist")
        ipnum = struct.unpack("i", inet_aton(black_ip_str))[0]
        ipv4_blacklist.__setitem__(ct.c_uint32(ipnum), ct.c_int(1));

b.attach_xdp(ifname, fn, flags)

print("Protection sampling interval %s seconds, threshold %s npkts" %
      (config_sample_secs, config_sample_threshold))
print("Blacklist sampling interval %s seconds, threshold %s npkts" %
      (config_blacklist_sample_secs, config_blacklist_sample_threshold))
print("DOS protection of %s, hit CTRL+C to stop" % ifname)
print("%-16s %-16s %-16s %-16s %-8s" %
      ("SADDR", "SADDR_PKTS", "SAMPLE_PKTS", "SAMPLE_TIME", "FLAGS"))

while 1:
    try:
        for k, v in sorted(ipv4_stat.items(), key=lambda ipv4_stat: ipv4_stat[0].saddr):
            saddr = inet_ntop(AF_INET, struct.pack("I", k.saddr))
            print("%-16s %-16ld %-16ld %-16ld %s" %
                  (saddr, v.npkt, v.sample_npkt, v.sample_start,
                   decode_addr_flags(v.flags)))
        time.sleep(1)
    except KeyboardInterrupt:
        print("Removing filter from device")
        break

b.remove_xdp(ifname, flags)
