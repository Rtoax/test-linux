#!/bin/bash
set -ex

if [[ $(basename $0) == sched_act.sh ]]; then
	OBJ=sched_act.bpf.o
	SEC=action
fi

[[ -z ${IF} ]] && IF=lo
[[ -z ${OBJ} ]] && OBJ=tc.bpf.o
[[ -z ${SEC} ]] && SEC="tcx/ingress"

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
