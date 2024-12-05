#!/usr/bin/python
# @lint-avoid-python-3-compatibility-imports
import os
import sys
import time

from bcc import BPF, libbcc

# support_lsm() 函数检查系统是否支持 BTF 和具有 bpf_lsm_bpf 函数变量，
# 并不能反应 LSM BPF 是否可以工作
if not BPF.support_lsm():
    print("LSM not supported")
    exit()

prog = """
#include <uapi/asm-generic/errno-base.h>
LSM_PROBE(bpf, int cmd, union bpf_attr *attr, unsigned int size)
{
    bpf_trace_printk("LSM BPF hook Worked");
    return -EPERM;
}
"""

print("bpf(2) will return EPERM!!!")

b = BPF(text=prog)
b.trace_print()
