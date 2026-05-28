#!/bin/bash
set -e

echo "bpf_jit_enable = $(cat /proc/sys/net/core/bpf_jit_enable)"
echo "bpf_jit_harden = $(sudo cat /proc/sys/net/core/bpf_jit_harden)"
echo "bpf_jit_kallsyms = $(sudo cat /proc/sys/net/core/bpf_jit_kallsyms)"
echo "bpf_jit_limit = $(sudo cat /proc/sys/net/core/bpf_jit_limit)"

jited=$(sudo bpftool prog list | grep -oE 'jited [0-9]+' | \
		awk 'BEGIN {sum=0} {sum+=$2} END {printf(sum"B\n")}')
echo "jited = ${jited}"
