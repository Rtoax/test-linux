#!/bin/bash

sudo bpftrace -l usdt:/lib64/libc.so.6:*
