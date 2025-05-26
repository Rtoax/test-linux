#!/bin/bash
# ref: https://medium.com/coccoc-engineering-blog/kvm-guests-cpu-flags-5d3ac9525421

sudo virsh cpu-models x86_64
# $ grep -m1 '^model name' /proc/cpuinfo
# VM with default custom mode
# model name : QEMU Virtual CPU version 2.5+
# VM with host passthrough mode
# model name : Intel(R) Xeon(R) CPU E5-2620 0 @ 2.00GHz
# VM with host model mode
# model name : Intel Core Processor (Broadwell)
