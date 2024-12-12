#!/usr/bin/python
# @lint-avoid-python-3-compatibility-imports

from __future__ import print_function
import os
import sys
import time
import atexit
import argparse

from bcc import BPF, BPFAttachType, lib


examples = """examples:
    # create cgroupv2
    sudo mkdir a.mnt
    sudo mount -t cgroupv2 none a.mnt
    sudo mkdir a.mnt/foo

    # run script
    sudo ./sockops.py -c a.mnt/foo

    # start a new bash, attach pid to cgroup foo, and run a tcp server
    echo $$ | sudo tee .../a.mnt/foo/cgroup.procs
    nc -l localhost

    # then, run client
    nc localhost
"""
parser = argparse.ArgumentParser(
        description="pipe data across multiple sockets",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=examples)
parser.add_argument("-c", "--cgroup", required=True,
        help="Specify the cgroup address. Note. must be cgroup2")

bpf_text = '''
#include <net/sock.h>

int sockops1(struct bpf_sock_ops *skops)
{
    bpf_trace_printk("call sock_ops ...");
    return 0;
}
'''

args = parser.parse_args()
bpf = BPF(text=bpf_text)
func_sock_ops = bpf.load_func("sockops1", bpf.SOCK_OPS)
# raise if error
cgroup_fd = os.open(args.cgroup, os.O_RDONLY)
bpf.attach_func(func_sock_ops, cgroup_fd, BPFAttachType.CGROUP_SOCK_OPS)

def detach_all():
    bpf.detach_func(func_sock_ops, cgroup_fd, BPFAttachType.CGROUP_SOCK_OPS)
    print("Detaching...")

atexit.register(detach_all)

while True:
    try:
        bpf.trace_print()
        sleep(1)
    except KeyboardInterrupt:
        sys.exit(0)
