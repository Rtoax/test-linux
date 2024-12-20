#pragma once
#include <linux/bpf.h>
#include <bpf/libbpf.h>

#define bpf(cmd, attr, size) sys_bpf(cmd, attr, size)

int sys_bpf(int cmd, union bpf_attr *attr, unsigned int size);
