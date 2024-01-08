#!/bin/bash

sudo bpftrace -l uprobe:/lib64/ld-linux-x86-64.so.2:*
