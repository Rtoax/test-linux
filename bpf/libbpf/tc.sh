#!/bin/bash
set -ex

[[ -z ${IF} ]] && IF=lo

OBJ=tc.bpf.o
SEC="tc"

cleanup() {
	sudo tc qdisc delete dev ${IF} clsact || true
}
trap cleanup EXIT

# Try remove exist clsact first
# Fix: Error: Exclusivity flag on, cannot modify.
cleanup

sudo tc qdisc add dev ${IF} clsact
sudo tc qdisc show dev ${IF} clsact

sudo tc filter add dev ${IF} ingress bpf object-file ${OBJ} section ${SEC}

# Show tracing
sudo cat /sys/kernel/tracing/trace_pipe
