#!/bin/bash
set -e
sudo bpftrace -l usdt:/lib64/ld-linux-x86-64.so.2:*
