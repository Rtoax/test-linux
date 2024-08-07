#!/bin/bash
sudo bpftrace -l uprobe:/usr/bin/gdb:* | grep opcode
