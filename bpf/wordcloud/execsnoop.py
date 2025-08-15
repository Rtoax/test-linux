#!/usr/bin/env python
#
# Record exec file
#
# Licensed under the Apache License, Version 2.0 (the "License")
#
# 2023-10-30    Rong Tao    Create this.

from __future__ import print_function
from bcc import ArgString, BPF
from bcc.utils import printb
import argparse
import os
from time import strftime
import logging
from systemd.journal import JournalHandler

# arguments
parser = argparse.ArgumentParser(
    description="Add some description",
    formatter_class=argparse.RawDescriptionHelpFormatter)
parser.add_argument("-L", "--journal", action="store_true",
    help="log to systemd.journal")
parser.add_argument("-T", "--text", help="output exec 'filename' to text file")

args = parser.parse_args()
journal = args.journal
output_text = args.text

if output_text:
    output_fp = open(output_text, 'w', encoding='utf-8')


bpf_text = """
#include <linux/fs.h>

struct data_t {
    char filename[128];
};
BPF_PERF_OUTPUT(exec_events);

static int commit_filename(void *args, const char *filename) {
    struct data_t data = {};
    bpf_probe_read(&data.filename, sizeof(data.filename), filename);
    exec_events.perf_submit((void *)args, &data, sizeof(data));
    return 0;
}

TRACEPOINT_PROBE(syscalls, sys_enter_execve) {
    return commit_filename(args, args->filename);
}
"""

def record_filename(filename):
    filename = os.path.basename(filename)
    if filename == 'vte-urlencode-cwd':
        return
    if filename == 'pk-command-not-found':
        return
    output_fp.write(filename + '\n')
    output_fp.flush()

def print_exec_event(cpu, data, size):
    event = b["exec_events"].event(data)
    printb(b"%-8s %-16s" %
           (strftime("%H:%M:%S").encode('ascii'),
            event.filename))
    if output_text:
        filename = event.filename.decode("utf-8")
        record_filename(filename)

if journal:
    log = logging.getLogger('some.name')
    log.addHandler(JournalHandler())
    log.setLevel(logging.INFO)
    log.info(b"sent to journal: %d" % (1))

b = BPF(text=bpf_text)

print("Tracing exec ... Hit Ctrl-C to end")
print("%-8s %-16s" % ("TIME", "FILENAME"))

b["exec_events"].open_perf_buffer(print_exec_event)

while True:
    try:
        b.perf_buffer_poll()
    except KeyboardInterrupt:
        exit()
        output_fp.close()
