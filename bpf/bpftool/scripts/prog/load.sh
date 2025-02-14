#!/bin/bash
set -ex

make -C ../../../libbpf/ tracepoint

[[ -z ${BPFTOOL} ]] && BPFTOOL=bpftool

PROG=../../../libbpf/tracepoint.bpf.o
PINNED=/sys/fs/bpf/tp_1

cleanup() {
	sudo rm -f ${PINNED}
}
trap cleanup EXIT

sudo ${BPFTOOL} prog load ${PROG} ${PINNED}
sudo ${BPFTOOL} prog show pinned ${PINNED} --json --pretty

# Dump eBPF instructions of the programs from the kernel.
sudo ${BPFTOOL} prog dump xlated pinned ${PINNED}
sudo ${BPFTOOL} prog dump xlated pinned ${PINNED} visual
# Dump jited image (host machine code) of the program.
sudo ${BPFTOOL} prog dump jited pinned ${PINNED}

# TODO: Failed
sudo ${BPFTOOL} prog attach pinned ${PINNED} tracepoint syscalls/sys_enter_execve
