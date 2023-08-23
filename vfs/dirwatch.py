#!/usr/bin/env python
#
# dirwatch.py - Monitor directory file changes
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2023-08-23    Rong Tao    Create this.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.containers import filter_by_containers
from bcc.utils import printb
import argparse
import os
from time import strftime


# arguments
parser = argparse.ArgumentParser(
    description="Add some description",
    formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("-D", "--directory", default="-1",
    help="specify directory to watch")
parser.add_argument("-V", "--verbose", action="store_true",
    help="show verbose")

args = parser.parse_args()
directory = args.directory
verbose = args.verbose


bpf_text = """
#include <linux/fs.h>
#include <linux/dcache.h>

enum op {
    OP_UNLINK,
};

struct my_data {
    u32 pid;
    char comm[TASK_COMM_LEN];
    u64 ino;
    enum op op;
};

BPF_PERF_OUTPUT(inode_events);

static int trace_inode_events(struct pt_regs *ctx, enum op op,
                              struct inode *inode)
{
    u32 pid = bpf_get_current_pid_tgid() >> 32;

    /* Skip negative */
    if (!inode)
        return 0;

    struct my_data data = {};

    bpf_get_current_comm(&data.comm, sizeof(data.comm));
    data.pid = pid;
    data.ino = inode->i_ino;
    data.op = op;

    inode_events.perf_submit(ctx, &data, sizeof(data));

    return 0;
}

TRACE_UNLINK
{
    struct inode *inode = dentry->d_inode;
    return trace_inode_events(ctx, OP_UNLINK, inode);
}
"""

# Oldest one
trace_unlink_func_1="""
int trace_unlink(struct pt_regs *ctx, struct inode *dir, struct dentry *dentry)
"""

# kernel commit 6521f8917082("namei: prepare for idmapped mounts") add argument
# 'struct user_namespace'.
trace_unlink_func_2="""
int trace_unlink(struct pt_regs *ctx, struct user_namespace *mnt_userns,
                 struct inode *dir, struct dentry *dentry)
"""

# kernel commit abf08576afe3("fs: port vfs_*() helpers to struct mnt_idmap")
# use mnt_idmap instead of user_namespace.
trace_unlink_func_3="""
int trace_unlink(struct pt_regs *ctx, struct mnt_idmap *idmap,
                 struct inode *dir, struct dentry *dentry)
"""


def print_inode_event(cpu, data, size):
    event = b["inode_events"].event(data)
    printb(b"%-8s %-8d %-16s %-16d" %
        (strftime("%H:%M:%S").encode('ascii'),
         event.pid,
         event.comm,
         event.ino))

# Store inode:pathname key value pairs.
hash_ino_file = {}

def file_info(pathname):
    info = os.stat(pathname)
    if verbose:
        print("%s ino %d" % (pathname, info.st_ino))
    hash_ino_file[info.st_ino] = pathname

def recursive_listdir(path):
    files = os.listdir(path)

    for file in files:
        file_path = os.path.join(path, file)

        if os.path.isfile(file_path):
            file_info(file_path)
        elif os.path.isdir(file_path):
            recursive_listdir(file_path)

if directory == "-1":
    print("Must specify a directory with -D, --directory")
    exit()
if not os.path.isdir(directory):
    print("%s is not directory" % directory)
    exit()

recursive_listdir(directory)
if verbose:
    print(hash_ino_file)


if BPF.kernel_struct_has_field(b'renamedata', b'new_mnt_idmap') == 1:
    bpf_text = bpf_text.replace('TRACE_UNLINK', trace_unlink_func_3)
elif BPF.kernel_struct_has_field(b'renamedata', b'old_mnt_userns') == 1:
    bpf_text = bpf_text.replace('TRACE_UNLINK', trace_unlink_func_2)
else:
    bpf_text = bpf_text.replace('TRACE_UNLINK', trace_unlink_func_1)

b = BPF(text=bpf_text)
b.attach_kprobe(event="vfs_unlink", fn_name="trace_unlink")

print("Tracing file remove ... Hit Ctrl-C to end")
print("%-8s %-8s %-16s %-16s" %
        ("TIME", "PID", "COMM", "INODE"))
b["inode_events"].open_perf_buffer(print_inode_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
