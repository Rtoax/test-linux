#!/bin/bash

sudo bpftrace -l usdt:/usr/libexec/qemu-kvm:*
