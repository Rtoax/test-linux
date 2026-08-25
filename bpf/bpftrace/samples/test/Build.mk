bpftrace-y += base.bt
bpftrace-y += system.bt

BT_ARGS := --test
BT_ARGS_system.bt := --unsafe
