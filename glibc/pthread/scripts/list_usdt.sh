#!/bin/bash

sudo bpftrace -l usdt:/lib64/libpthread.so:*
