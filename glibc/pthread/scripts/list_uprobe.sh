#!/bin/bash

sudo bpftrace -l uprobe:/lib64/libpthread.so:*
