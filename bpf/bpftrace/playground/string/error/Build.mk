subdir-y += assignment

bpftrace-y += for.bt
bpftrace-y += plus.bt

BT_ENVS_for.bt := --expect-return 255
BT_ENVS_plus.bt := --expect-return 1
