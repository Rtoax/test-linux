#!/bin/bash

sudo bpftrace -l uprobe:/lib64/libc.so.6:*
