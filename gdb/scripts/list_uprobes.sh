#!/bin/bash
set -e
sudo bpftrace -l uprobe:/usr/bin/gdb:*
