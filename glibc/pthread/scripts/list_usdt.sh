#!/bin/bash

so=/lib64/libpthread.so.0

sudo bpftrace -l usdt:${so}:*
